"""
avxjudge.py is a tool that RPM builds use when building for AVX2 or AVX512 
optimisations. It attempts to heuristically guess whether the library file has 
enough AVX instructions to be worth keeping.
"""
#!/usr/bin/python3
import subprocess
import sys
import re
import argparse
import os

# MMX and SSE2 instructions
sse_instructions_xmm = set([
    "paddb", "paddd", "paddsb", "paddsw", "paddusb", "psubw",
    "paddusw", "paddw", "pmaddwd", "pmulhw", "pmullw", "psubb", "psubsb",
    "psubsw", "psubusb", "paddusw", "paddw", "pmaddwd", "pmulhw", "pmullw",
    "psubb", "psubd", "psubd", "psubsb", "psubsw", "psubusb", "psubusw"
])

# 0.1 value instructions
avx2_instructions_lv = set(["shrx", "rorx", "shlx", "shrx", "shrx", "movbe"])
avx2_instructions_ymm = set([
    "vpaddq", "vpaddd", "vpsubq", "vpsubd", "vmulpd", "vaddpd", "vsubpd",
    "vmulps", "vaddps", "vsubps", "vpmaxsq", "vpminsq", "vpmuludq",
    "vpand", "vpmaxud", "vpminud", "vpmaxsd", "vpmaxsw", "vpminsd",
    "vpminsw", "vpand", "vpor", "vpmulld"
])
avx512_instructions_lv = set()

# 1.0 value instructions
avx2_instructions = set([
    "vfmadd132ss", "vfmadd213ss", "vfmadd231ss", "vfmadd132sd",
    "vfmadd231sd", "vfmadd213sd",
    "vfmsub132ss", "vfmsub213ss", "vfmsub231ss", "vfmsub132sd", "vfmsub231sd",
    "vfmsub213sd",
    "vfnmadd132ss", "vfnmadd213ss", "vfnmadd231ss", "vfnmadd132sd",
    "vfnmadd231sd", "vfnmadd213sd",
    "vfnmsub132ss", "vfnmsub213ss", "vfnmsub231ss", "vfnmsub132sd",
    "vfnmsub231sd", "vfnmsub213sd",
])
avx512_instructions = set()

# 2.0 value instructions
avx2_instructions_hv = set([
    "vpclmulhqlqdq", "vpclmullqhqdq",
    "vfmadd132ps", "vfmadd213ps", "vfmadd231ps", "vfmadd132pd", "vfmadd231pd",
    "vfmadd213pd", "vfmsub132ps", "vfmsub213ps", "vfmsub231ps", "vfmsub132pd",
    "vfmsub231pd", "vfmsub213pd",
    "vfnmadd132ps", "vfnmadd213ps", "vfnmadd231ps", "vfnmadd132pd",
    "vfnmadd231pd", "vfnmadd213pd", "vfnmsub132ps", "vfnmsub213ps",
    "vfnmsub231ps", "vfnmsub132pd", "vfnmsub231pd", "vfnmsub213pd", "vdivpd",
])
avx512_instructions_hv = set()

# Minimum thresholds for keeping libraries
min_count = 10
min_score = 1.0

debug = 0

class FunctionRecord():
    def __init__(self):
        self.scores = {"sse": 0.0, "avx2": 0.0, "avx512": 0.0}
        self.counts = {"sse": 0, "avx2": 0, "avx512": 0}
        self.instructions = 0
        self.name = ""


class RecordKeeper():
    def __init__(self, delete_type):
        self.total_counts = {"sse": 0, "avx2": 0, "avx512": 0}
        self.total_scores = {"sse": 0.0, "avx2": 0.0, "avx512": 0.0}
        self.functions = {"sse": dict(), "avx2": dict(), "avx512": dict()}
        self.ratios = {"sse": dict(), "avx2": dict(), "avx512": dict()}
        self.function_record = FunctionRecord()
        self.delete_type = delete_type

    def should_delete(self) -> bool:
        if self.delete_type and self.total_counts[self.delete_type] < min_count and self.total_scores[self.delete_type] <= min_score:
            return True
        return False

    def finalize_function_attrs(self):
        for i in ("sse", "avx2", "avx512"):
            if self.function_record.counts[i] >= 1:
                self.functions[i][self.function_record.name] = self.function_record.scores[i]
                self.ratios[i][self.function_record.name] = 100.0 * self.function_record.counts[i] / self.function_record.instructions
            self.total_scores[i] += self.function_record.scores[i]
            self.total_counts[i] += self.function_record.counts[i]


def is_sse(instruction:str, args:str) -> float:

    val: float = -1.0
    if "xmm" in args:
        if ("pd" in instruction or "ps" in instruction or instruction in sse_instructions_xmm):
            val = 1.0
        else:
            val = 0.01
    return val


def is_avx2(instruction:str, args:str) -> float:
    val: float = -1.0

    if "ymm" in args:
        if ("pd" in instruction or "ps" in instruction or instruction in avx2_instructions_ymm) and "xor" not in instruction and "vmov" not in instruction:
            val = 1.0
        else:
            val = 0.01

    if instruction in avx2_instructions_lv:
        val = max(val, 0.1)
    if instruction in avx2_instructions:
        val = max(val, 1.0)
    if instruction in avx2_instructions_hv:
        val = max(val, 2.0)

    return val

def has_high_register(args: str) -> bool:
    return args.endswith((
        'mm16', 'mm17', 'mm18', 'mm19', 'mm20', 'mm21', 'mm22',
        'mm23', 'mm24', 'mm25', 'mm26', 'mm27', 'mm28', 'mm29',
        'mm30', 'mm31'
    ))

def is_avx512(instruction:str, args:str) -> float:
    val: float = -1.0

    if instruction in avx512_instructions_lv:
        val = max(val, 0.1)
    if instruction in avx512_instructions:
        val = max(val, 1.0)
    if instruction in avx512_instructions_hv:
        val = max(val, 2.0)

    if "xor" not in instruction and "ymm" in args and has_high_register(args):
        val = max(val, 0.02)
    if "xor" not in instruction and has_high_register(args):
        val = max(val, 0.01)

    if "zmm" in args:
        if ("pd" in instruction or "ps" in instruction or "vpadd" in instruction or "vpsub" in instruction or instruction in avx2_instructions_ymm) and "xor" not in instruction and "vmov" not in instruction:
            val = max(val, 1.0)
        else:
            val = max(val, 0.01)


    return val


def ratio(f: float) -> str:
    f = f * 100
    f = round(f)/100.0
    return str(f)

def print_top_functions(records:RecordKeeper) -> None:
    def summarize(table: dict, is_pct: bool, max_funcs: int = 5) -> None:
        for f in sorted(table, key=table.get, reverse=True)[:max_funcs]:
            f = "    %-30s\t%s" % (f, ratio(table[f]))

            if is_pct:
                print(f, "%s")
            else:
                print(f)

    sets = (
        ("SSE", records.functions["sse"], records.ratios["sse"]),
        ("AVX2", records.functions["avx2"], records.ratios["avx2"]),
        ("AVX512", records.functions["avx512"], records.ratios["avx512"]),
    )

    for set_name, funcs, funcs_ratio in sets:
        print("Top %s functions by instruction count" % set_name)
        summarize(funcs_ratio, True)
        print()

        print("Top %s functions by value" % set_name)
        summarize(funcs, False)
        print()

sse_avx2_duplicate_cnt = 0
avx2_avx512_duplicate_cnt = 0

def process_objdump_line(records:RecordKeeper, line:str, verbose:int, quiet:int) -> None:
    sse_score = -1.0
    avx2_score = -1.0
    avx512_score = -1.0
    sse_str = " "
    avx2_str = " "
    avx512_str = ""

    global sse_avx2_duplicate_cnt
    global avx2_avx512_duplicate_cnt
    global debug

    match = re.search("^(.*)\#.*", line)
    if match:
        line = match.group(1)

    match = re.search(".*[0-9a-f]+\:\t[0-9a-f\ ]+\t([a-zA-Z0-9]+) (.*)", line)
    if match:
        ins = match.group(1)
        arg = match.group(2)

        avx512_score = is_avx512(ins, arg)
        if avx512_score <= 0:
            avx2_score = is_avx2(ins, arg)
        if avx2_score <= 0 and avx512_score <= 0:
            sse_score = is_sse(ins, arg)

        records.function_record.instructions += 1

    match = re.search("\<([a-zA-Z0-9_@\.\-]+)\>\:", line)
    if match:
        records.function_record.name = match.group(1)
        if records.function_record.instructions > 0 and verbose > 0:
            print(records.function_record.name,
                  "\t", ratio(records.function_record.counts["sse"] / records.function_record.instructions),
                  "\t", ratio(records.function_record.counts["avx2"] / records.function_record.instructions),
                  "\t", ratio(records.function_record.counts["avx512"] / records.function_record.instructions),
                  "\t", records.function_record.scores["sse"],
                  "\t", records.function_record.scores["avx2"],
                  "\t", records.function_record.scores["avx512"])
        if records.function_record.instructions > 0:
            records.finalize_function_attrs()
            records.function_record = FunctionRecord()

    if sse_score >= 0.0:
        sse_str = str(sse_score)
        records.function_record.scores["sse"] += sse_score
        records.function_record.counts["sse"] += 1

    if avx2_score >= 0.0:
        avx2_str = str(avx2_score)
        records.function_record.scores["avx2"] += avx2_score
        records.function_record.counts["avx2"] += 1

    if avx512_score >= 0.0:
        avx512_str = str(avx512_score)
        records.function_record.scores["avx512"] += avx512_score
        records.function_record.counts["avx512"] += 1

    if sse_score >=0.0 and avx2_score >= 0.0 and debug:
        sse_avx2_duplicate_cnt +=1
        print("duplicate count for sse & avx2 ?", ins, arg, sse_avx2_duplicate_cnt)

    if avx512_score >= 0.0 and avx2_score >= 0.0 and debug:
        avx2_avx512_duplicate_cnt +=1
        print("duplicate count for avx2 & avx512 ?", ins, arg, avx2_avx512_duplicate_cnt)

    if not records.should_delete() and quiet != 0:
        sys.exit(0)

    if verbose > 0:
        print(sse_str,"\t",avx2_str,"\t", avx512_str,"\t", line)


def do_file(filename: str, verbose:int, quiet:int, delete_type:str) -> None:
    global debug

    records = RecordKeeper(delete_type)

    if quiet == 0:
        print("Analyzing", filename)

    p = subprocess.Popen(["objdump","-d", filename], stdout=subprocess.PIPE)
    for line in p.stdout:
        process_objdump_line(records, line.decode("latin-1"), verbose, quiet)
    output, _ =  p.communicate()
    for line in output.decode("latin-1").splitlines():
        process_objdump_line(records, line, verbose, quiet)
    if quiet <= 0:
        print_top_functions(records)
        print()
        print("File total (SSE): ", records.total_counts["sse"],"instructions with score", round(records.total_scores["sse"]))
        print("File total (AVX2): ", records.total_counts["avx2"],"instructions with score", round(records.total_scores["avx2"]))
        print("File total (AVX512): ", records.total_counts["avx512"],"instructions with score", round(records.total_scores["avx512"]))
        print()
    if debug:
        print("File duplicate count of sse&avx2", sse_avx2_duplicate_cnt, ", duplicate count of avx2&avx512", avx2_avx512_duplicate_cnt)

    if records.should_delete():
        print(filename, "\t", delete_type, "count:", records.total_counts[delete_type],"\t", delete_type, "value:", ratio(records.total_scores[delete_type]))
        try:
            os.unlink(filename)
        except:
            None


def main():
    global debug

    verbose = 0
    quiet = 0
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--verbose", help="increase output verbosity", action="store_true")
    parser.add_argument("-q", "--quiet", help="decrease output verbosity", action="store_true")
    parser.add_argument("-d", "--debug", help="print out more debug info", action="store_true")
    parser.add_argument("filename", help = "The filename to inspect")
    group = parser.add_mutually_exclusive_group()
    group.add_argument("-1", "--unlinksse", help="unlink the file if it has no SSE instructions", action="store_true")
    group.add_argument("-2", "--unlinkavx2", help="unlink the file if it has no AVX2 instructions", action="store_true")
    group.add_argument("-5", "--unlinkavx512", help="unlink the file if it has no AVX512 instructions", action="store_true")

    args = parser.parse_args()
    if args.verbose:
        verbose = 1

    if args.quiet:
        verbose = 0
        quiet = 1

    if args.debug:
        debug = 1

    if args.unlinksse:
        deltype = "sse"
    elif args.unlinkavx2:
        deltype = "avx2"
    elif args.unlinkavx512:
        deltype = "avx512"
    else:
        deltype = ""

    do_file(args.filename, verbose, quiet, deltype)


if __name__ == '__main__':
    main()
