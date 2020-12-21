/*
 * lmon.c -- Curses based Performance Monitor for Linux
 * with saving performance stats to a CSV file mode.
 * Developer: Nigel Griffiths. 
 * (C) Copyright 2009 Nigel Griffiths

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Use the following Makefile (for Linux on POWER)
CFLAGS=-g -Wall -D POWER 
LDFLAGS=-lcurses -lm
nmon: lmon.o
 * end of Makefile
 */
/* Other #ifdef's for specific features or platforms
Platforms: POWER MAINFRAME X86 ARM - Mandatory one of these at a time
Specific Linux versions: RHEL7 SLES113 SLES12
Specific feature: NVIDIA_GPU
Bug / missing feature workarounds:
	REREAD - for RHEL3
	LSBLK_NO_TYPE - SLES11.3 has not lsblk disk TYPE option

Options which should always but switched on:
SMALLMEM - removes huge memory, dirty, whritebak, mapped, slab, pagethreads as not in older kernels
PRE_KERNEL_2_6_18 1 kernel levels before removed the following to the disk stats 
	pi_num_threads, 
	pi_rt_priority, 
	pi_policy, 
	pi_delayacct_blkio_ticks 
*/

/* note: RAW assumes you are using the index "i" to select the CPU */
#define RAW(member)      (long)((long)(p->cpuN[i].member)   - (long)(q->cpuN[i].member))
#define RAWTOTAL(member) (long)((long)(p->cpu_total.member) - (long)(q->cpu_total.member))

#define VERSION "16m"
char version[] = VERSION;
static char *SccsId = "nmon " VERSION;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>
#include <signal.h>
#include <pwd.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/utsname.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/wait.h>

/* Windows moved here so they can be cleared when the screen mode changes */
WINDOW *padwelcome = NULL;
WINDOW *padtop = NULL;
WINDOW *padmem = NULL;
WINDOW *padlarge = NULL;
WINDOW *padpage = NULL;
WINDOW *padker = NULL;
WINDOW *padnet = NULL;
WINDOW *padneterr = NULL;
WINDOW *padnfs = NULL;
WINDOW *padres = NULL;
WINDOW *padsmp = NULL;
WINDOW *padutil = NULL;
WINDOW *padwide = NULL;
WINDOW *padgpu = NULL;
WINDOW *padmhz = NULL;
WINDOW *padlong = NULL;
WINDOW *paddisk = NULL;
WINDOW *paddg = NULL;
WINDOW *padmap = NULL;
WINDOW *padjfs = NULL;
#ifdef POWER
WINDOW *padlpar = NULL;
#endif
WINDOW *padverb = NULL;
WINDOW *padhelp = NULL;


/* for Disk Busy rain style output covering 100's of diskss on one screen */
const char disk_busy_map_ch[] =
    "_____.....----------++++++++++oooooooooo0000000000OOOOOOOOOO8888888888XXXXXXXXXX##########@@@@@@@@@@*";
/*"00000555551111111111222222222233333333334444444444555555555566666666667777777777888888888899999999991"*/

int extended_disk = 0;		/* report additional data from /proc/diskstats to spreadsheet output */

#define FLIP(variable) if(variable) variable=0; else variable=1;

#ifdef MALLOC_DEBUG
#define MALLOC(argument)        mymalloc(argument,__LINE__)
#define FREE(argument)          myfree(argument,__LINE__)
#define REALLOC(argument1,argument2)    myrealloc(argument1,argument2,__LINE__)
void *mymalloc(int size, int line)
{
    void *ptr;
    ptr = malloc(size);
    fprintf(stderr, "0x%x = malloc(%d) at line=%d\n", ptr, size, line);
    return ptr;
}

void myfree(void *ptr, int line)
{
    fprintf(stderr, "free(0x%x) at line=%d\n", ptr, line);
    free(ptr);
}

void *myrealloc(void *oldptr, int size, int line)
{
    void *ptr;
    ptr = realloc(oldptr, size);
    fprintf(stderr, "0x%x = realloc(0x%x, %d) at line=%d\n", ptr, oldptr,
	    size, line);
    return ptr;
}
#else
#define MALLOC(argument)        malloc(argument)
#define FREE(argument)          free(argument)
#define REALLOC(argument1,argument2)    realloc(argument1,argument2)
#endif				/* MALLOC STUFF */

#ifdef NVIDIA_GPU
typedef int nvmlReturn_t;
#define NVML_SUCCESS 0

typedef struct nvmlUtilization_st {
    unsigned int gpu;
    unsigned int memory;
} nvmlUtilization_t;

struct nvmlDevice_st;
typedef struct nvmlDevice_st *nvmlDevice_t;

nvmlReturn_t nvmlInit(void);
nvmlReturn_t nvmlShutdown(void);
nvmlReturn_t nvmlDeviceGetCount(unsigned int *count);
nvmlReturn_t nvmlDeviceGetHandleByIndex(unsigned int index,
					nvmlDevice_t * device);
nvmlReturn_t nvmlDeviceGetUtilizationRates(nvmlDevice_t device,
					   nvmlUtilization_t *
					   utilization);
nvmlReturn_t nvmlSystemGetDriverVersion(char *version, int count);
nvmlReturn_t nvmlSystemGetNVMLVersion(char *version, int count);
nvmlReturn_t nvmlDeviceGetName(nvmlDevice_t device, char *name, int count);
nvmlReturn_t nvmlDeviceGetTemperature(nvmlDevice_t device, int type,
				      unsigned int *temp);
nvmlReturn_t nvmlDeviceGetPowerUsage(nvmlDevice_t device,
				     unsigned int *watts);
nvmlReturn_t nvmlDeviceGetClockInfo(nvmlDevice_t device, int type,
				    unsigned int *mhz);

#define NVML_TEMPERATURE_GPU 0
#define NVML_CLOCK_GRAPHICS 0

nvmlDevice_t gpu_device[4];
nvmlUtilization_t gpu_util[4];
unsigned int gpu_devices;
char gpu_name[4][1024];
unsigned int gpu_temp[4];
unsigned int gpu_watts[4];
unsigned int gpu_clock[4];
char gpu_driver_version[1024];
char gpu_nvml_version[1024];
int first_time_gpu = 1;

void gpu_init()
{
    int i;
    nvmlReturn_t nvres;
    if ((nvres = nvmlInit()) != NVML_SUCCESS) {
	printf("nvmlInit failed %d\n", nvres);
	return;
    }

    if ((nvres =
	 nvmlSystemGetDriverVersion(&gpu_driver_version[0],
				    1024)) != NVML_SUCCESS) {
	printf("nvmlSystemGetDriverVersion failed %d\n", nvres);
	return;
    }
    if ((nvres =
	 nvmlSystemGetNVMLVersion(&gpu_nvml_version[0],
				  1024)) != NVML_SUCCESS) {
	printf("nvmlSystemGetDriverVersion failed %d\n", nvres);
	return;
    }

    if ((nvres = nvmlDeviceGetCount(&gpu_devices)) != NVML_SUCCESS) {
	printf("nvmlDeviceGetCount failed %d\n", nvres);
	return;
    }
    if (gpu_devices > 4)
	gpu_devices = 4;

    for (i = 0; i < gpu_devices; i++) {
	if (nvmlDeviceGetHandleByIndex(i, &gpu_device[i]) != NVML_SUCCESS) {
	    printf("nvmlDeviceGetHandleByIndex(%d) failed %d\n", i, nvres);
	    return;
	}
    }
}
#endif				/* NVIDIA_GPU */

#define P_CPUINFO	0
#define P_STAT		1
#define P_VERSION	2
#define P_MEMINFO   	3
#define P_UPTIME   	4
#define P_LOADAVG   	5
#define P_NFS   	6
#define P_NFSD   	7
#define P_VMSTAT	8	/* new in 13h */
#define P_NUMBER	9	/* one more than the max */

char *month[12] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
    "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

/* Cut of everything after the first space in callback
 * Delete any '&' just before the space
 */
char *check_call_string(char *callback, const char *name)
{
    char *tmp_ptr = callback;

    if (strlen(callback) > 256) {
	fprintf(stderr, "ERROR nmon: ignoring %s - too long\n", name);
	return (char *) NULL;
    }

    for (; *tmp_ptr != '\0' && *tmp_ptr != ' ' && *tmp_ptr != '&';
	 ++tmp_ptr);

    *tmp_ptr = '\0';

    if (tmp_ptr == callback)
	return (char *) NULL;
    else
	return callback;
}

/* Remove error output to this buffer and display it if NMONDEBUG=1 */
char errorstr[70];
int error_on = 0;
void error(char *err)
{
    strncpy(errorstr, err, 69);
    errorstr[69] = 0;
}

/*
 * lscpu command output save
*/
int lscpu_available = 0;

struct {
    char *arch;
    char *byte_order;
#define ORDER_UNKNOWN 0
#define ORDER_LITTLE  1
#define ORDER_BIG     2
    int order;
    int cpus;
    char *cpu_online;
    char *cpu_offline;
    int threads;
    int cores;
    int sockets;
    int numa_nodes;
    char *model;
    char *model_name;
    int mhz;
    int mhz_min;
    int mhz_max;
} lscpu;

void lscpu_init()
{
    FILE *pop;
    int len;
    int data_col = 21;
#define LSCPU_STRLEN 512
    char tmpstr[LSCPU_STRLEN + 1];

    if (lscpu_available == 1)
	return;
    pop = popen("/usr/bin/lscpu 2>/dev/null", "r");
    if (pop != NULL) {
	lscpu_available = 1;
	tmpstr[0] = 0;
	while (fgets(tmpstr, LSCPU_STRLEN, pop) != NULL) {
	    tmpstr[strlen(tmpstr) - 1] = 0;	/* remove newline */
	    if (strncmp("Architecture:", tmpstr, strlen("Architecture:")) == 0) {

		/* Architecture:        SOMETHING OR OTHER
		   0123456789012345678901 
		                 |->    ^                     */
		/* start from char after the :<space> looking for some leters or numbers */
		len = strlen(tmpstr);
		for(data_col=14;data_col<len;data_col++) {
		   if(isalnum(tmpstr[data_col]))
	 		break;
		}

		lscpu.arch = MALLOC(strlen(&tmpstr[data_col]) + 1);
		strcpy(lscpu.arch, &tmpstr[data_col]);
	    }
	    if (strncmp("Byte Order:", tmpstr, strlen("Byte Order:")) == 0) {
		lscpu.byte_order = MALLOC(strlen(&tmpstr[data_col]) + 1);
		strcpy(lscpu.byte_order, &tmpstr[data_col]);
		if (strncmp
		    ("Little Endian", lscpu.byte_order,
		     strlen("Little Endian")) == 0) {
		    lscpu.order = ORDER_LITTLE;
		}
		if (strncmp
		    ("Big Endian", lscpu.byte_order,
		     strlen("Big Endian")) == 0) {
		    lscpu.order = ORDER_BIG;
		}
	    }
	    if (strncmp("CPU(s):", tmpstr, strlen("CPU(s):")) == 0) {
		sscanf(&tmpstr[data_col], "%d", &lscpu.cpus);
	    }
	    if (strncmp
		("On-line CPU(s) list:", tmpstr,
		 strlen("On-line CPU(s) list:")) == 0) {
		lscpu.cpu_online = MALLOC(strlen(&tmpstr[data_col]) + 1);
		strcpy(lscpu.cpu_online, &tmpstr[data_col]);
	    }
	    if (strncmp
		("Off-line CPU(s) list:", tmpstr,
		 strlen("Off-line CPU(s) list:")) == 0) {
		lscpu.cpu_offline =
		    MALLOC(strlen(&tmpstr[data_col]) + 1);
		strcpy(lscpu.cpu_offline, &tmpstr[data_col]);
	    }
	    if (strncmp("Model:", tmpstr, strlen("Model:")) == 0) {
		lscpu.model = MALLOC(strlen(&tmpstr[data_col]) + 1);
		strcpy(lscpu.model, &tmpstr[data_col]);
	    }
	    if (strncmp("Model name:", tmpstr, strlen("Model name:")) == 0) {
		lscpu.model_name = MALLOC(strlen(&tmpstr[data_col]) + 1);
		strcpy(lscpu.model_name, &tmpstr[data_col]);
	    }
	    if (strncmp
		("Thread(s) per core:", tmpstr,
		 strlen("Thread(s) per core:")) == 0) {
		sscanf(&tmpstr[data_col], "%d", &lscpu.threads);
	    }
	    if (strncmp
		("Core(s) per socket:", tmpstr,
		 strlen("Core(s) per socket:")) == 0) {
		sscanf(&tmpstr[data_col], "%d", &lscpu.cores);
	    }
	    if (strncmp("Socket(s):", tmpstr, strlen("Socket(s):")) == 0) {
		sscanf(&tmpstr[data_col], "%d", &lscpu.sockets);
	    }
	    if (strncmp("NUMA node(s):", tmpstr, strlen("NUMA node(s):"))
		== 0) {
		sscanf(&tmpstr[data_col], "%d", &lscpu.numa_nodes);
	    }
	    if (strncmp("CPU MHz:", tmpstr, strlen("CPU MHz:")) == 0) {
		sscanf(&tmpstr[data_col], "%d", &lscpu.mhz);
	    }
	    if (strncmp("CPU max MHz:", tmpstr, strlen("CPU max MHz:")) ==
		0) {
		sscanf(&tmpstr[data_col], "%d", &lscpu.mhz_max);
	    }
	    if (strncmp("CPU min MHz:", tmpstr, strlen("CPU min MHz:")) ==
		0) {
		sscanf(&tmpstr[data_col], "%d", &lscpu.mhz_min);
	    }
	}
	pclose(pop);
    }

}

/* Maximum number of lines in /proc files */
/* Intel already has 26 (so here 30) per Hypterthread CPU (max 128*2 CPUs here) */
/* POWER has only 6 to 7 lines but gets  1536 SMT threads soon */
/* Erring on the saf side below */
#define PROC_MAXLINES (16*1024)	/*MAGIC COOKIE WARNING */


int proc_cpu_done = 0;		/* Flag if we have run function proc_cpu() already in this interval */

int reread = 0;
struct {
    FILE *fp;
    char *filename;
    int size;
    int lines;
    char *line[PROC_MAXLINES];
    char *buf;
    int read_this_interval;	/* track updates for each update to stop  double data collection */
} proc[P_NUMBER];

void proc_init()
{
    proc[P_CPUINFO].filename = "/proc/cpuinfo";
    proc[P_STAT].filename = "/proc/stat";
    proc[P_VERSION].filename = "/proc/version";
    proc[P_MEMINFO].filename = "/proc/meminfo";
    proc[P_UPTIME].filename = "/proc/uptime";
    proc[P_LOADAVG].filename = "/proc/loadavg";
    proc[P_NFS].filename = "/proc/net/rpc/nfs";
    proc[P_NFSD].filename = "/proc/net/rpc/nfsd";
    proc[P_VMSTAT].filename = "/proc/vmstat";
}

void proc_read(int num)
{
    int i;
    int size;
    int found;
    char buf[1024];

    if (proc[num].read_this_interval == 1)
	return;

    if (proc[num].fp == 0) {
	if ((proc[num].fp = fopen(proc[num].filename, "r")) == NULL) {
	    snprintf(buf, 1024,"failed to open file %s", proc[num].filename);
	    error(buf);
	    proc[num].fp = 0;
	    return;
	}
    }
    rewind(proc[num].fp);

    /* We re-read P_STAT, now flag proc_cpu() that it has to re-process that data */
    if (num == P_STAT)
	proc_cpu_done = 0;

    if (proc[num].size == 0) {
	/* first time so allocate  initial now */
	proc[num].buf = MALLOC(512);
	proc[num].size = 512;
    }

    for (i = 0; i < 4096; i++) {	/* MAGIC COOKIE WARNING  POWER8 default install can have 2655 processes */
	size = fread(proc[num].buf, 1, proc[num].size - 1, proc[num].fp);
	if (size < proc[num].size - 1)
	    break;
	proc[num].size += 512;
	proc[num].buf = REALLOC(proc[num].buf, proc[num].size);
	rewind(proc[num].fp);
    }

    proc[num].buf[size] = 0;
    proc[num].lines = 0;
    proc[num].line[0] = &proc[num].buf[0];
    if (num == P_VERSION) {
	found = 0;
	for (i = 0; i < size; i++) {	/* remove some weird stuff found the hard way in various Linux versions and device drivers */
	    /* place ") (" on two lines */
	    if (found == 0 &&
		proc[num].buf[i] == ')' &&
		proc[num].buf[i + 1] == ' ' &&
		proc[num].buf[i + 2] == '(') {
		proc[num].buf[i + 1] = '\n';
		found = 1;
	    } else {
		/* place ") #" on two lines */
		if (proc[num].buf[i] == ')' &&
		    proc[num].buf[i + 1] == ' ' &&
		    proc[num].buf[i + 2] == '#') {
		    proc[num].buf[i + 1] = '\n';
		}
		/* place "#1" on two lines */
		if (proc[num].buf[i] == '#' && proc[num].buf[i + 2] == '1') {
		    proc[num].buf[i] = '\n';
		}
	    }
	}
    }
    for (i = 0; i < size; i++) {
	/* replace Tab characters with space */
	if (proc[num].buf[i] == '\t') {
	    proc[num].buf[i] = ' ';
	} else if (proc[num].buf[i] == '\n') {
	    /* replace newline characters with null */
	    proc[num].lines++;
	    proc[num].buf[i] = '\0';
	    proc[num].line[proc[num].lines] = &proc[num].buf[i + 1];
	}
	if (proc[num].lines == PROC_MAXLINES - 1)
	    break;
    }
    if (reread) {
	fclose(proc[num].fp);
	proc[num].fp = 0;
    }
    /* Set flag so we do not re-read the data even if called multiple times in same interval */
    proc[num].read_this_interval = 1;
}

#include <dirent.h>

struct procsinfo {
    int pi_pid;
    char pi_comm[64];
    char pi_state;
    int pi_ppid;
    int pi_pgrp;
    int pi_session;
    int pi_tty_nr;
    int pi_tty_pgrp;
    unsigned long pi_flags;
    unsigned long pi_minflt;
    unsigned long pi_cmin_flt;
    unsigned long pi_majflt;
    unsigned long pi_cmaj_flt;
    unsigned long pi_utime;
    unsigned long pi_stime;
    long pi_cutime;
    long pi_cstime;
    long pi_pri;
    long pi_nice;
#ifdef PRE_KERNEL_2_6_18
    long junk /* removed */ ;
#else
    long pi_num_threads;
#endif
    long pi_it_real_value;
    unsigned long pi_start_time;
    unsigned long pi_vsize;
    long pi_rss;		/* - 3 */
    unsigned long pi_rlim_cur;
    unsigned long pi_start_code;
    unsigned long pi_end_code;
    unsigned long pi_start_stack;
    unsigned long pi_esp;
    unsigned long pi_eip;
    /* The signal information here is obsolete. */
    unsigned long pi_pending_signal;
    unsigned long pi_blocked_sig;
    unsigned long pi_sigign;
    unsigned long pi_sigcatch;
    unsigned long pi_wchan;
    unsigned long pi_nswap;
    unsigned long pi_cnswap;
    int pi_exit_signal;
    int pi_cpu;
#ifndef PRE_KERNEL_2_6_18
    unsigned long pi_rt_priority;
    unsigned long pi_policy;
    unsigned long long pi_delayacct_blkio_ticks;
#endif
    unsigned long statm_size;	/* total program size */
    unsigned long statm_resident;	/* resident set size */
    unsigned long statm_share;	/* shared pages */
    unsigned long statm_trs;	/* text (code) */
    unsigned long statm_drs;	/* data/stack */
    unsigned long statm_lrs;	/* library */
    unsigned long statm_dt;	/* dirty pages */

    unsigned long long read_io;	/* storage read bytes */
    unsigned long long write_io;	/* storage write bytes */
};
int isroot = 0;

#include <mntent.h>
#include <fstab.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <net/if.h>

int debug = 0;
time_t timer;			/* used to work out the hour/min/second */

/* Counts of resources */
int cpus = 1;			/* number of CPUs in system (lets hope its more than zero!) */
#if X86 || ARM
int cores = 0;
int siblings = 0;
int processorchips = 0;
int hyperthreads = 0;
char *vendor_ptr = "not-set";
char *model_ptr = "not-set";
char *mhz_ptr = "not-set";
char *bogo_ptr = "not-set";
#endif
int old_cpus = 1;		/* Number of CPU seen in previuos interval */
int max_cpus = 1;		/* highest number of CPUs in DLPAR */
int networks = 0;		/* number of networks in system  */
int partitions = 0;		/* number of partitions in system  */
int partitions_short = 0;	/* partitions file data short form (i.e. data missing) */
int disks = 0;			/* number of disks in system  */
int seconds = -1;		/* pause interval */
int maxloops = -1;		/* stop after this number of updates */
char hostname[256];
char run_name[256];
int run_name_set = 0;
char fullhostname[256];
int loop;

#define DPL 150			/* Disks per line for file output to ensure it 
				   does not overflow the spreadsheet input line max */

int disks_per_line = DPL;

#define NEWDISKGROUP(disk) ( (disk) % disks_per_line == 0)

/* Mode of output variables */
int show_aaa = 1;
int show_para = 1;
int show_headings = 1;
int show_res = 0;
int show_smp = 0;
int show_util = 0;
int first_util = 1;
int show_wide = 0;
int show_gpu = 0;
int show_mhz = 0;
int show_longterm = 0;
int show_disk = 0;
#define SHOW_DISK_NONE  0
#define SHOW_DISK_STATS 1
#define SHOW_DISK_GRAPH 2
int show_diskmap = 0;
int show_memory = 0;
int show_large = 0;
int show_kernel = 0;
int show_nfs = 0;
int show_net = 0;
int show_neterror = 0;
int show_help = 0;
int show_top = 0;
int show_topmode = 1;
#define ARGS_NONE 0
#define ARGS_ONLY 1
int show_args = 0;
int show_all = 1;		/* 1=all procs& disk 0=only if 1% or more busy */
int show_verbose = 0;
int show_jfs = 0;
int show_jfs_minimum = 0;
int flash_on = 0;
int first_huge = 1;
int first_steal = 1;
long huge_peak = 0;
int welcome = 1;
int dotline = 0;
int show_rrd = 0;
int show_lpar = 0;
int show_vm = 0;
int show_dgroup = 0;		/* disk groups */
int auto_dgroup = 0;		/* disk groups defined via -g auto */
int disk_only_mode = 0;		/* disk stats shows disks only if user used -g auto */
int dgroup_loaded = 0;		/* 0 = no, 1=needed, 2=loaded */

#define RRD if(show_rrd)

double ignore_procdisk_threshold = 0.1;
double ignore_io_threshold = 0.1;
/* Curses support */
#define CURSE if(cursed)	/* Only use this for single line curses calls */
#define COLOUR if(colour)	/* Only use this for single line colour curses calls */
int cursed = 1;			/* 1 = using curses and 
				   0 = loging output for a spreadsheet */
int colour = 1;			/* 1 = using colour curses and 
				   0 = using black and white curses  (see -b flag) */
#define MVPRINTW(row,col,string) {move((row),(col)); \
					attron(A_STANDOUT); \
					printw(string); \
					attroff(A_STANDOUT); }
FILE *fp;			/* filepointer for spreadsheet output */


char *timestamp(int loop, time_t eon)
{
    static char string[64];
    if (show_rrd)
	snprintf(string, 64, "%ld", (long) eon);
    else
	snprintf(string, 64, "T%04d", loop);
    return string;
}

#define LOOP timestamp(loop,timer)

char *easy[5] = { "not found", 0, 0, 0, 0 };
char *lsb_release[5] = { "not found", 0, 0, 0, 0 };

void find_release()
{
    FILE *pop;
    int i;
    char tmpstr[1024+1];

#if defined(SLES12) || defined(SLES15)
    pop = popen("cat /etc/os-release 2>/dev/null", "r");
#else
    pop = popen("cat /etc/*ease 2>/dev/null", "r");
#endif				/* SLES12 */
    if (pop != NULL) {
	tmpstr[0] = 0;
	for (i = 0; i < 4; i++) {
	    if (fgets(tmpstr, 1024, pop) == NULL)
		break;
	    tmpstr[strlen(tmpstr) - 1] = 0;	/* remove newline */
	    easy[i] = MALLOC(strlen(tmpstr) + 1);
	    strcpy(easy[i], tmpstr);
	}
	pclose(pop);
    }
    pop = popen("/usr/bin/lsb_release -idrc 2>/dev/null", "r");
    if (pop != NULL) {
	tmpstr[0] = 0;
	for (i = 0; i < 4; i++) {
	    if (fgets(tmpstr, 70, pop) == NULL)
		break;
	    tmpstr[strlen(tmpstr) - 1] = 0;	/* remove newline */
	    lsb_release[i] = MALLOC(strlen(tmpstr) + 1);
	    strcpy(lsb_release[i], tmpstr);
	}
	pclose(pop);
    }
}



/* Full Args Mode stuff here */

#define ARGSMAX 1024*8
#define CMDLEN 4096

struct {
    int pid;
    char *args;
} arglist[ARGSMAX];

void args_output(int pid, int loop, char *progname)
{
    FILE *pop;
    int i, j, n;
    char tmpstr[CMDLEN];
    static int arg_first_time = 1;

    if (pid == 0)
	return;			/* ignore init */
    for (i = 0; i < ARGSMAX - 1; i++) {	/* clear data out */
	if (arglist[i].pid == pid) {
	    return;
	}
	if (arglist[i].pid == 0)	/* got to empty slot */
	    break;
    }
    snprintf(tmpstr, CMDLEN, "ps -p %d -o args 2>/dev/null", pid);
    pop = popen(tmpstr, "r");
    if (pop == NULL) {
	return;
    } else {
	if (fgets(tmpstr, CMDLEN, pop) == NULL) {	/* throw away header */
	    pclose(pop);
	    return;
	}
	tmpstr[0] = 0;
	if (fgets(tmpstr, CMDLEN, pop) == NULL) {
	    pclose(pop);
	    return;
	}
	tmpstr[strlen(tmpstr) - 1] = 0;
	if (tmpstr[strlen(tmpstr) - 1] == ' ')
	    tmpstr[strlen(tmpstr) - 1] = 0;
	arglist[i].pid = pid;
	if (arg_first_time) {
	    fprintf(fp, "UARG,+Time,PID,ProgName,FullCommand\n");
	    arg_first_time = 0;
	}
	n = strlen(tmpstr);
	for (i = 0; i < n; i++) {
	    /*strip out stuff that confused Excel i.e. starting with maths symbol */
	    if (tmpstr[i] == ',' &&
		((tmpstr[i + 1] == '-') || tmpstr[i + 1] == '+'))
		tmpstr[i + 1] = '_';
	    /*strip out double spaces */
	    if (tmpstr[i] == ' ' && tmpstr[i + 1] == ' ') {
		for (j = 0; j < n - i; j++)
		    tmpstr[i + j] = tmpstr[i + j + 1];
		i--;		/* rescan to remove triple space etc */
	    }
	}

	fprintf(fp, "UARG,%s,%07d,%s,%s\n", LOOP, pid, progname, tmpstr);
	pclose(pop);
	return;
    }
}

void args_load()
{
    FILE *pop;
    int i;
    char tmpstr[CMDLEN];

    for (i = 0; i < ARGSMAX; i++) {	/* clear data out */
	if (arglist[i].pid == -1)
	    break;
	if (arglist[i].pid != 0) {
	    arglist[i].pid = -1;
	    free(arglist[i].args);
	}
    }
    pop = popen("ps -eo pid,args 2>/dev/null", "r");
    if (pop == NULL) {
	return;
    } else {
	if (fgets(tmpstr, CMDLEN, pop) == NULL) {	/* throw away header */
	    pclose(pop);
	    return;
	}
	for (i = 0; i < ARGSMAX; i++) {
	    tmpstr[0] = 0;
	    if (fgets(tmpstr, CMDLEN, pop) == NULL) {
		pclose(pop);
		return;
	    }
	    tmpstr[strlen(tmpstr) - 1] = 0;
	    if (tmpstr[strlen(tmpstr) - 1] == ' ')
		tmpstr[strlen(tmpstr) - 1] = 0;
	    arglist[i].pid = atoi(tmpstr);
	    arglist[i].args = MALLOC(strlen(tmpstr) + 1);
	    strcpy(arglist[i].args, &tmpstr[6]);
	}
	pclose(pop);
    }
}

char *args_lookup(int pid, char *progname)
{
    int i;
    for (i = 0; i < ARGSMAX; i++) {
	if (arglist[i].pid == pid)
	    return arglist[i].args;
	if (arglist[i].pid == -1)
	    return progname;
    }
    return progname;
}

/* end args mode stuff here */

void linux_bbbp(char *name, char *cmd, char *err)
{
    int i;
    int j;
    int len;
#define STRLEN 4096
    char str[STRLEN];
    FILE *pop;
    static int lineno = 0;

    pop = popen(cmd, "r");
    if (pop == NULL) {
	fprintf(fp, "BBBP,%03d,%s failed to run %s\n", lineno++, cmd, err);
    } else {
	fprintf(fp, "BBBP,%03d,%s\n", lineno++, name);
	for (i = 0; i < 2048 && (fgets(str, STRLEN, pop) != NULL); i++) {	/* 2048=sanity check only */
	    len = strlen(str);
	    if (len > STRLEN)
		len = STRLEN;
	    if (str[len - 1] == '\n')	/*strip off the newline */
		str[len - 1] = 0;
	    /* fix text starting characters that confuses spread sheets */
	    if (str[0] == '+')
		str[0] = 'p';
	    if (str[0] == '*')
		str[0] = 'm';
	    if (str[0] == '-')
		str[0] = 'n';
	    if (str[0] == '/')
		str[0] = 'd';
	    if (str[0] == '=')
		str[0] = 'e';
	    /* remove double quotes as it confuses spread sheets */
	    for (j = 0; str[j] != 0; j++)
		if (str[j] == '"')
		    str[j] = 'Q';
	    fprintf(fp, "BBBP,%03d,%s,\"%s\"\n", lineno++, name, str);
	}
	pclose(pop);
    }
}

#define WARNING "needs root permission or file not present"

/* Global name of programme for printing it */
char *progname;

/* Seconds since epoc and the sting version */
long long boottime = 0;
char boottime_str[64] = "not found";
/* Main data structure for collected stats.
 * Two versions are previous and current data.
 * Often its the difference that is printed.
 * The pointers are swaped i.e. current becomes the previous
 * and the previous over written rather than moving data around.
 */
struct cpu_stat {		/* changed the order here to match this years kernel (man 5 /proc/stat) */
    long long user;
    long long nice;
    long long sys;
    long long idle;
    long long wait;		/* for IO */
    long long irq;
    long long softirq;
    long long steal;
    long long guest;
    long long guest_nice;
    /* below are non-cpu based numbers in the same file */
    long long intr;
    long long ctxt;
    long long procs;
    long long running;
    long long blocked;
    float uptime;
    float idletime;
    float mins1;
    float mins5;
    float mins15;
};

#define ulong unsigned long
struct dsk_stat {
    char dk_name[32];
    int dk_major;
    int dk_minor;
    long dk_noinfo;
    ulong dk_reads;
    ulong dk_rmerge;
    ulong dk_rmsec;
    ulong dk_rkb;
    ulong dk_writes;
    ulong dk_wmerge;
    ulong dk_wmsec;
    ulong dk_wkb;
    ulong dk_xfers;
    ulong dk_bsize;
    ulong dk_time;
    ulong dk_inflight;
    ulong dk_backlog;
    ulong dk_partition;
    ulong dk_blocks;		/* in /proc/partitions only */
    ulong dk_use;
    ulong dk_aveq;
};

struct mem_stat {
    long memtotal;
    long memfree;
    long memshared;
    long buffers;
    long cached;
    long swapcached;
    long active;
    long inactive;
    long hightotal;
    long highfree;
    long lowtotal;
    long lowfree;
    long swaptotal;
    long swapfree;
#ifndef SMALLMEM
    long dirty;
    long writeback;
    long mapped;
    long slab;
    long committed_as;
    long pagetables;
    long hugetotal;
    long hugefree;
    long hugesize;
#else
    long bigfree;
#endif /*SMALLMEM*/
};

struct vm_stat {
    long long nr_dirty;
    long long nr_writeback;
    long long nr_unstable;
    long long nr_page_table_pages;
    long long nr_mapped;
    long long nr_slab;
    long long nr_slab_reclaimable;
    long long nr_slab_unreclaimable;
    long long pgpgin;
    long long pgpgout;
    long long pswpin;
    long long pswpout;
    long long pgalloc_high;
    long long pgalloc_normal;
    long long pgalloc_dma;
    long long pgfree;
    long long pgactivate;
    long long pgdeactivate;
    long long pgfault;
    long long pgmajfault;
    long long pgrefill_high;
    long long pgrefill_normal;
    long long pgrefill_dma;
    long long pgsteal_high;
    long long pgsteal_normal;
    long long pgsteal_dma;
    long long pgscan_kswapd_high;
    long long pgscan_kswapd_normal;
    long long pgscan_kswapd_dma;
    long long pgscan_direct_high;
    long long pgscan_direct_normal;
    long long pgscan_direct_dma;
    long long pginodesteal;
    long long slabs_scanned;
    long long kswapd_steal;
    long long kswapd_inodesteal;
    long long pageoutrun;
    long long allocstall;
    long long pgrotated;
};


#define NFS_V2_NAMES_COUNT 18
char *nfs_v2_names[NFS_V2_NAMES_COUNT] = {
    "null", "getattr", "setattr", "root", "lookup", "readlink",
    "read", "wrcache", "write", "create", "remove", "rename",
    "link", "symlink", "mkdir", "rmdir", "readdir", "fsstat"
};

#define NFS_V3_NAMES_COUNT 22
char *nfs_v3_names[22] = {
    "null", "getattr", "setattr", "lookup", "access", "readlink",
    "read", "write", "create", "mkdir", "symlink", "mknod",
    "remove", "rmdir", "rename", "link", "readdir", "readdirplus",
    "fsstat", "fsinfo", "pathconf", "commit"
};

#define NFS_V4S_NAMES_COUNT 72
int nfs_v4s_names_count = NFS_V4S_NAMES_COUNT;
char *nfs_v4s_names[NFS_V4S_NAMES_COUNT] = {	/* get these names from nfsstat as they are NOT documented */
    "op0-unused", "op1-unused", "op2-future", "access", "close", "commit",	/* 1 - 6 */
    "create", "delegpurge", "delegreturn", "getattr", "getfh", "link",	/* 7 - 12 */
    "lock", "lockt", "locku", "lookup", "lookup_root", "nverify",	/* 13 - 18 */
    "open", "openattr", "open_conf", "open_dgrd", "putfh", "putpubfh",	/* 19 - 24 */
    "putrootfh", "read", "readdir", "readlink", "remove", "rename",	/* 25 - 30 */
    "renew", "restorefh", "savefh", "secinfo", "setattr", "setcltid",	/* 31 - 36 */
    "setcltidconf", "verify", "write", "rellockowner", "bc_ctl", "blind_conn",	/* 37 - 42 */
    "exchange_id", "create_ses", "destroy_ses", "free_statid", "getdirdelag", "getdevinfo",	/* 43 - 48 */
    "getdevlist", "layoutcommit", "layoutget", "layoutreturn", "secunfononam", "sequence",	/* 49 - 54 */
    "set_ssv", "test_stateid", "want_deleg", "destory_clid", "reclaim_comp", "stat60",	/* 55 - 60 */
    "stat61", "stat62", "stat63", "stat64", "stat65", "stat66",	/* 61 - 66 */
    "stat67", "stat68", "stat69", "stat70", "stat71", "stat72"	/* 67 - 72 */
};

#define NFS_V4C_NAMES_COUNT 60
int nfs_v4c_names_count = NFS_V4C_NAMES_COUNT;
char *nfs_v4c_names[NFS_V4C_NAMES_COUNT] = {	/* get these names from nfsstat as they are NOT documented */
    "null", "read", "write", "commit", "open", "open_conf",	/* 1 - 6 */
    "open_noat", "open_dgrd", "close", "setattr", "fsinfo", "renew",	/* 7 - 12 */
    "setclntid", "confirm", "lock", "lockt", "locku", "access",	/* 13 - 18 */
    "getattr", "lookup", "lookup_root", "remove", "rename", "link",	/* 19 - 24 */
    "symlink", "create", "pathconf", "statfs", "readlink", "readdir",	/* 25 - 30 */
    "server_caps", "delegreturn", "getacl", "setacl", "fs_locations", "rel_lkowner",	/* 31 - 36 */
    "secinfo", "exchange_id", "create_ses", "destroy_ses", "sequence", "get_lease_t",	/* 37 - 42 */
    "reclaim_comp", "layoutget", "getdevinfo", "layoutcommit", "layoutreturn", "getdevlist",	/* 43 - 48 */
    "stat49", "stat50", "stat51", "stat52", "start53", "stat54",	/* 49 - 54 */
    "stat55", "stat56", "stat57", "stat58", "start59", "stat60"	/* 55 - 60 */
};


int nfs_v2c_found = 0;
int nfs_v2s_found = 0;
int nfs_v3c_found = 0;
int nfs_v3s_found = 0;
int nfs_v4c_found = 0;
int nfs_v4s_found = 0;
int nfs_clear = 0;

struct nfs_stat {
    long v2c[NFS_V2_NAMES_COUNT];	/* verison 2 client */
    long v3c[NFS_V3_NAMES_COUNT];	/* verison 3 client */
    long v4c[NFS_V4C_NAMES_COUNT];	/* verison 4 client */
    long v2s[NFS_V2_NAMES_COUNT];	/* verison 2 SERVER */
    long v3s[NFS_V3_NAMES_COUNT];	/* verison 3 SERVER */
    long v4s[NFS_V4S_NAMES_COUNT];	/* verison 4 SERVER */
};

#define NETMAX 32
struct net_stat {
    unsigned long if_name[17];
    unsigned long long if_ibytes;
    unsigned long long if_obytes;
    unsigned long long if_ipackets;
    unsigned long long if_opackets;
    unsigned long if_ierrs;
    unsigned long if_oerrs;
    unsigned long if_idrop;
    unsigned long if_ififo;
    unsigned long if_iframe;
    unsigned long if_odrop;
    unsigned long if_ofifo;
    unsigned long if_ocarrier;
    unsigned long if_ocolls;
};
#ifdef PARTITIONS
#define PARTMAX 256
struct part_stat {
    int part_major;
    int part_minor;
    unsigned long part_blocks;
    char part_name[16];
    unsigned long part_rio;
    unsigned long part_rmerge;
    unsigned long part_rsect;
    unsigned long part_ruse;
    unsigned long part_wio;
    unsigned long part_wmerge;
    unsigned long part_wsect;
    unsigned long part_wuse;
    unsigned long part_run;
    unsigned long part_use;
    unsigned long part_aveq;
};
#endif /*PARTITIONS*/
#ifdef POWER
#define VM_UNKNOWN 0
#define VM_POWERVM 1
#define VM_POWERKVM_GUEST 2
#define VM_POWERKVM_HOST 3
#define VM_NATIVE 4
int power_vm_type = VM_UNKNOWN;

/* XXXXXXX need to test if rewind() worked or not for lparcfg */
int lparcfg_reread = 1;
/* Reset at end of each interval so LPAR cfg is only read once each interval
 * even if proc_lparcfg() is called multiple times
 * Note: lparcfg is not read via proc_read() !
 */
int lparcfg_processed = 0;

struct {
    char version_string[16];	/*lparcfg 1.3 */
    int version;
    char serial_number[16];	/*HAL,0210033EA */
    char system_type[64];	/*HAL,9124-720 */
    /* new record is "IBM pSeries (emulated by qemu)" instead of "IBM 9119-MME" */
    int partition_id;		/*11 */
/* 
R4=0x14
R5=0x0
R6=0x800b0000
R7=0x1000000040004
*/
    int BoundThrds;			/*=1*/
    int CapInc;				/*=1*/
    long long DisWheRotPer;		/*=2070000*/
    int MinEntCap;			/*=10*/
    int MinEntCapPerVP;			/*=10*/
    int MinMem;				/*=2048*/
    int DesMem;				/*=4096*/
    int MinProcs;			/*=1*/
    int partition_max_entitled_capacity;/*=400*/
    int system_potential_processors;	/*=4*/
     /**/ int partition_entitled_capacity;
					/*=20*/
    int system_active_processors;	/*=4*/
    int pool_capacity;			/*=4*/
    int unallocated_capacity_weight;	/*=0*/
    int capacity_weight;		/*=0*/
    int capped;				/*=1*/
    int unallocated_capacity;		/*=0*/
    long long pool_idle_time;		/*=0*/
    long long pool_idle_saved;
    long long pool_idle_diff;
    int pool_num_procs;			/*=0*/
    long long purr;			/*=0*/
    long long purr_saved;
    long long purr_diff;
    long long timebase;
    int partition_active_processors;	/*=1*/
    int partition_potential_processors;	/*=40*/
    int shared_processor_mode;		/*=1*/
    int smt_mode;		/* 1: off, 2: SMT-2, 4: SMT-4 */
    int cmo_enabled;		/* 1 means AMS is Active */
    int entitled_memory_pool_number;	/*  pool number = 0 */
    int entitled_memory_weight;	/* 0 to 255 */
    long cmo_faults;		/* Hypervisor Page-in faults = big number */
    long cmo_faults_save;	/* above saved */
    long cmo_faults_diff;	/* delta */
    long cmo_fault_time_usec;	/* Hypervisor time in micro seconds = big */
    long cmo_fault_time_usec_save;	/* above saved */
    long cmo_fault_time_usec_diff;	/* delta */
    long backing_memory;	/* AIX pmem in bytes */
    long cmo_page_size;		/* AMS page size in bytes */
    long entitled_memory_pool_size;	/* AMS whole pool size in bytes */
    long entitled_memory_loan_request;	/* AMS requesting more memory loaning */

    long DedDonMode;
#ifdef EXPERIMENTAL
/* new data in SLES11 for POWER 2.6.27 (may be a little earlier too) */
    long DesEntCap;
    long DesProcs;
    long DesVarCapWt;
    long group;
    long pool;
    long entitled_memory;
    long entitled_memory_group_number;
    long unallocated_entitled_memory_weight;
    long unallocated_io_mapping_entitlement;
/* new data in SLES11 for POWER 2.6.27 */
#endif				/* EXPERIMENTAL */

} lparcfg;

int lpar_count = 0;

#define LPAR_LINE_MAX   100	/* MAGIC COOKIE WARNING */
#define LPAR_LINE_WIDTH 80
char lpar_buffer[LPAR_LINE_MAX][LPAR_LINE_WIDTH];

int lpar_sanity = 55;

char *locate(char *s)
{
    int i;
    int len;
    len = strlen(s);
    for (i = 0; i < lpar_count; i++)
	if (!strncmp(s, lpar_buffer[i], len))
	    return lpar_buffer[i];
    return "";
}

#define NUMBER_NOT_VALID -999

long long read_longlong(char *s)
{
    long long x;
    int ret;
    int len;
    int i;
    char *str;
    str = locate(s);
    len = strlen(str);
    if (len == 0) {
	return NUMBER_NOT_VALID;
    }
    for (i = 0; i < len; i++) {
	if (str[i] == '=') {
	    ret = sscanf(&str[i + 1], "%lld", &x);
	    if (ret != 1) {
		fprintf(stderr,
			"sscanf for %s failed returned = %d line=%s\n", s,
			ret, str);
		return -1;
	    }
/* fprintf(fp,"DEBUG read %s value %lld\n",s,x);*/
	    return x;
	}
    }
    fprintf(stderr, "read_long_long failed returned line=%s\n", str);
    return -2;
}


/* Return of 0 means data not available */
int proc_lparcfg()
{
    static FILE *fp = (FILE *) - 1;
/* Only try to read /proc/ppc64/lparcfg once - remember if it's readable */
    static int lparinfo_not_available = 0;
    int i;
    char *str;
    /* If we already read and processed /proc/lparcfg in this interval - just return */
    if (lparcfg_processed == 1)
	return 1;

    if (lparinfo_not_available == 1)
	return 0;

    if (fp == (FILE *) - 1) {
	if ((fp = fopen("/proc/ppc64/lparcfg", "r")) == NULL) {
	    error("failed to open - /proc/ppc64/lparcfg");
	    fp = (FILE *) - 1;
	    lparinfo_not_available = 1;
	    if (power_vm_type == VM_UNKNOWN) {
		/*  Heuristics for spotting PowerKVM Host
		   a) inside ifdef POWER so can't be x86
		   b) /proc/ppc64/lparcfg is missing
		   c) /etc/ *ease files have hints 
		   Confirmed true for IBM_POWERKVM 2.1 
		 */
		if (strncmp("IBM_PowerKVM", easy[1], 12) == 0)
		    power_vm_type = VM_POWERKVM_HOST;
		else
		    power_vm_type = VM_NATIVE;
	    }
	    return 0;
	}
    }

    for (lpar_count = 0; lpar_count < LPAR_LINE_MAX - 1; lpar_count++) {
	if (fgets(lpar_buffer[lpar_count], LPAR_LINE_WIDTH - 1, fp) ==
	    NULL)
	    break;
    }
    if (lparcfg_reread) {	/* XXXX  unclear if close+open is necessary   - unfortunately this requires version many of Linux on POWER install to test early releases */
	fclose(fp);
	fp = (FILE *) - 1;
    } else
	rewind(fp);

    str = locate("lparcfg");
    sscanf(str, "lparcfg %s", lparcfg.version_string);
    str = locate("serial_number");
    sscanf(str, "serial_number=%s", lparcfg.serial_number);
    str = locate("system_type");
    for (i = 0; i < strlen(str); i++)	/* Remove new spaces in massive string meaning PowerKVM Guest !! */
	if (str[i] == ' ')
	    str[i] = '-';
    sscanf(str, "system_type=%s", lparcfg.system_type);
    if (power_vm_type == VM_UNKNOWN) {
	/*  Heuristics for spotting PowerKVM Guest
	   a) inside ifdef POWER so can't be x86
	   b) we have a /proc/ppc64/lparcfg - probably mostly missing (1.9)
	   c) system type string includes "qemu" 
	   Confirmed true for SLES11.3 RHEL6.5 and Ubuntu 14.4.1
	 */
	if (strstr(lparcfg.system_type, "(emulated-by-qemu)") == 0)
	    power_vm_type = VM_POWERVM;	/* not found */
	else
	    power_vm_type = VM_POWERKVM_GUEST;
    }
#define GETDATA(variable) lparcfg.variable = read_longlong( __STRING(variable) );

    GETDATA(partition_id);
    GETDATA(BoundThrds);
    GETDATA(CapInc);
    GETDATA(DisWheRotPer);
    GETDATA(MinEntCap);
    GETDATA(MinEntCapPerVP);
    GETDATA(MinMem);
    GETDATA(DesMem);
    GETDATA(MinProcs);
    GETDATA(partition_max_entitled_capacity);
    GETDATA(system_potential_processors);
    GETDATA(partition_entitled_capacity);
    GETDATA(system_active_processors);
    GETDATA(pool_capacity);
    GETDATA(unallocated_capacity_weight);
    GETDATA(capacity_weight);
    GETDATA(capped);
    GETDATA(unallocated_capacity);
    lparcfg.pool_idle_saved = lparcfg.pool_idle_time;
    GETDATA(pool_idle_time);
    lparcfg.pool_idle_diff =
	lparcfg.pool_idle_time - lparcfg.pool_idle_saved;
    GETDATA(pool_num_procs);
    lparcfg.purr_saved = lparcfg.purr;
    GETDATA(purr);
    lparcfg.purr_diff = lparcfg.purr - lparcfg.purr_saved;
    GETDATA(partition_active_processors);
    GETDATA(partition_potential_processors);
    GETDATA(shared_processor_mode);
    /* Brute force, may provide temporary incorrect data during
     * dynamic reconfiguraiton envents
     */
    lparcfg.smt_mode = cpus / lparcfg.partition_active_processors;

    /* AMS additions */
    GETDATA(cmo_enabled);
    if (lparcfg.cmo_enabled == NUMBER_NOT_VALID) {
	lparcfg.cmo_enabled = 0;
    }
    if (lparcfg.cmo_enabled) {
	GETDATA(entitled_memory_pool_number);	/*  pool number = 0 */
	GETDATA(entitled_memory_weight);	/* 0 to 255 */

	lparcfg.cmo_faults_save = lparcfg.cmo_faults;
	GETDATA(cmo_faults);	/* Hypervisor Page-in faults = big number */
	lparcfg.cmo_faults_diff =
	    lparcfg.cmo_faults - lparcfg.cmo_faults_save;

	lparcfg.cmo_fault_time_usec_save = lparcfg.cmo_fault_time_usec;
	GETDATA(cmo_fault_time_usec);	/* Hypervisor time in micro seconds = big number */
	lparcfg.cmo_fault_time_usec_diff =
	    lparcfg.cmo_fault_time_usec - lparcfg.cmo_fault_time_usec_save;

	GETDATA(backing_memory);	/* AIX pmem in bytes */
	GETDATA(cmo_page_size);	/* AMS page size in bytes */
	GETDATA(entitled_memory_pool_size);	/* AMS whole pool size in bytes */
	GETDATA(entitled_memory_loan_request);	/* AMS requesting more memory loaning */

    }
    GETDATA(DedDonMode);
#ifdef EXPERIMENTAL
    GETDATA(DesEntCap);
    GETDATA(DesProcs);
    GETDATA(DesVarCapWt);
    GETDATA(group);
    GETDATA(pool);
    GETDATA(entitled_memory);
    GETDATA(entitled_memory_group_number);
    GETDATA(unallocated_entitled_memory_weight);
    GETDATA(unallocated_io_mapping_entitlement);
#endif				/* EXPERIMENTAL */

    lparcfg_processed = 1;
    return 1;
}
#endif /*POWER*/
#define DISKMIN 256
#define DISKMAX diskmax
int diskmax = DISKMIN;

/* Supports up to 780, but not POWER6 595 follow-up with POWER7 */
/* XXXX needs rework to cope to with fairly rare but interesting higher numbers of CPU machines */
#define CPUMAX (192 * 8)	/* MAGIC COOKIE WARNING */

struct data {
    struct dsk_stat *dk;
    struct cpu_stat cpu_total;
    struct cpu_stat cpuN[CPUMAX];
    struct mem_stat mem;
    struct vm_stat vm;
    struct nfs_stat nfs;
    struct net_stat ifnets[NETMAX];
#ifdef PARTITIONS
    struct part_stat parts[PARTMAX];
#endif /*PARTITIONS*/
    struct timeval tv;
    double time;
    struct procsinfo *procs;

    int proc_records;
    int processes;
} database[2], *p, *q;


long long get_vm_value(char *s)
{
    int currline;
    int currchar;
    long long result = -1;
    char *check;
    int len;
    int found;

    for (currline = 0; currline < proc[P_VMSTAT].lines; currline++) {
	len = strlen(s);
	for (currchar = 0, found = 1; currchar < len; currchar++) {
	    if (proc[P_VMSTAT].line[currline][currchar] == 0 ||
		s[currchar] != proc[P_VMSTAT].line[currline][currchar]) {
		found = 0;
		break;
	    }
	}
	if (found && proc[P_VMSTAT].line[currline][currchar] == ' ') {
	    result =
		strtoll(&proc[P_VMSTAT].line[currline][currchar + 1],
			&check, 10);
	    if (*check == proc[P_VMSTAT].line[currline][currchar + 1]) {
		fprintf(stderr, "%s has an unexpected format: >%s<\n",
			proc[P_VMSTAT].filename,
			proc[P_VMSTAT].line[currline]);
		return -1;
	    }
	    return result;
	}
    }
    return -1;
}

#define GETVM(variable) p->vm.variable = get_vm_value(__STRING(variable) );

int read_vmstat()
{
    proc_read(P_VMSTAT);
    if (proc[P_VMSTAT].read_this_interval == 0
	|| proc[P_VMSTAT].lines == 0)
	return (-1);

    /* Note: if the variable requested is not found in /proc/vmstat then it is set to -1 */
    GETVM(nr_dirty);
    GETVM(nr_writeback);
    GETVM(nr_unstable);
    GETVM(nr_page_table_pages);
    GETVM(nr_mapped);
    if(p->vm.nr_slab != -1)  
	    GETVM(nr_slab);
    if(p->vm.nr_slab == -1)  {
	    GETVM(nr_slab_reclaimable);
	    GETVM(nr_slab_unreclaimable);
    }
    GETVM(pgpgin);
    GETVM(pgpgout);
    GETVM(pswpin);
    GETVM(pswpout);
    GETVM(pgalloc_high);
    GETVM(pgalloc_normal);
    GETVM(pgalloc_dma);
    GETVM(pgfree);
    GETVM(pgactivate);
    GETVM(pgdeactivate);
    GETVM(pgfault);
    GETVM(pgmajfault);
    GETVM(pgrefill_high);
    GETVM(pgrefill_normal);
    GETVM(pgrefill_dma);
    GETVM(pgsteal_high);
    GETVM(pgsteal_normal);
    GETVM(pgsteal_dma);
    GETVM(pgscan_kswapd_high);
    GETVM(pgscan_kswapd_normal);
    GETVM(pgscan_kswapd_dma);
    GETVM(pgscan_direct_high);
    GETVM(pgscan_direct_normal);
    GETVM(pgscan_direct_dma);
    GETVM(pginodesteal);
    GETVM(slabs_scanned);
    GETVM(kswapd_steal);
    GETVM(kswapd_inodesteal);
    GETVM(pageoutrun);
    GETVM(allocstall);
    GETVM(pgrotated);
    return 1;
}


/* These macro simplify the access to the Main data structure */
#define DKDELTA(member) ( (q->dk[i].member > p->dk[i].member) ? 0 : (p->dk[i].member - q->dk[i].member))
#define SIDELTA(member) ( (q->si.member > p->si.member)       ? 0 : (p->si.member - q->si.member))

#define IFNAME 64

#define TIMEDELTA(member,index1,index2) ((p->procs[index1].member) - (q->procs[index2].member))
#define IODELTA(member,index1,index2) ( (q->procs[index2].member > p->procs[index1].member) ? 0 : (p->procs[index1].member - q->procs[index2].member) )
#define COUNTDELTA(member) ( (q->procs[topper[j].other].member > p->procs[i].member) ? 0 : (p->procs[i].member  - q->procs[topper[j].other].member) )

#define TIMED(member) ((double)(p->procs[i].member.tv_sec))

double *cpu_peak;		/* ptr to array  - 1 for each cpu - 0 = average for machine */
double *disk_busy_peak;
double *disk_rate_peak;
double net_read_peak[NETMAX];
double net_write_peak[NETMAX];
int aiorunning;
int aiorunning_max = 0;
int aiocount;
int aiocount_max = 0;
float aiotime;
float aiotime_max = 0.0;

char *dskgrp(int i)
{
    static char error_string[] = { "Too-Many-Disks" };
    static char *string[16] = { "", "1", "2", "3",
	"4", "5", "6", "7",
	"8", "9", "10", "11",
	"12", "13", "14", "15"
    };

    i = (int) ((float) i / (float) disks_per_line);
    if (0 <= i && i <= 15)
	return string[i];
    return error_string;
}

/* command checking against a list */

#define CMDMAX 64

char *cmdlist[CMDMAX];
int cmdfound = 0;

int cmdcheck(char *cmd)
{
    int i;
#ifdef CMDDEBUG
    fprintf(stderr, "cmdfound=%d\n", cmdfound);
    for (i = 0; i < cmdfound; i++)
	fprintf(stderr, "cmdlist[%d]=\"%s\"\n", i, cmdlist[i]);
#endif				/* CMDDEBUG */
    for (i = 0; i < cmdfound; i++) {
	if (strlen(cmdlist[i]) == 0)
	    continue;
	if (!strncmp(cmdlist[i], cmd, strlen(cmdlist[i])))
	    return 1;
    }
    return 0;
}

/* Convert secs + micro secs to a double */
double doubletime(void)
{

    gettimeofday(&p->tv, 0);
    return ((double) p->tv.tv_sec + p->tv.tv_usec * 1.0e-6);
}

void get_cpu_cnt()
{
    int i;

    /* Get CPU info from /proc/stat and populate proc[P_STAT] */
    proc_read(P_STAT);

    /* Start with index [1] as [0] contains overall CPU statistics */
    for (i = 1; i < proc[P_STAT].lines; i++) {
	if (strncmp("cpu", proc[P_STAT].line[i], 3) == 0)
	    cpus = i;
	else
	    break;
    }
    if (cpus > CPUMAX) {
	printf
	    ("This nmon supports only %d CPU threads (Logical CPUs) and the machine appears to have %d.\nnmon stopping as its unsafe to continue.\n",
	     CPUMAX, cpus);
	exit(44);
    }
}

#if X86 || ARM
void get_intel_spec()
{
    int i;
    int physicalcpu[256];
    int id;

    /* Get CPU info from /proc/stat and populate proc[P_STAT] */
    proc_read(P_CPUINFO);

    for (i = 0; i < 256; i++)
	physicalcpu[i] = 0;

    for (i = 0; i < proc[P_CPUINFO].lines; i++) {
	if (strncmp("vendor_id", proc[P_CPUINFO].line[i], 9) == 0) {
	    vendor_ptr = &proc[P_CPUINFO].line[i][12];
	}
    }
    for (i = 0; i < proc[P_CPUINFO].lines; i++) {
	if (strncmp("model name", proc[P_CPUINFO].line[i], 10) == 0) {
	    model_ptr = &proc[P_CPUINFO].line[i][13];
	}
    }
    for (i = 0; i < proc[P_CPUINFO].lines; i++) {
	if (strncmp("cpu MHz", proc[P_CPUINFO].line[i], 7) == 0) {
	    mhz_ptr = &proc[P_CPUINFO].line[i][11];
	}
    }
    for (i = 0; i < proc[P_CPUINFO].lines; i++) {
	if((strncmp("bogomips", proc[P_CPUINFO].line[i], 8) == 0) ||
	   (strncmp("bogoMIPS", proc[P_CPUINFO].line[i], 8) == 0) ||
	   (strncmp("BogoMIPS", proc[P_CPUINFO].line[i], 8) == 0)){
	    bogo_ptr = &proc[P_CPUINFO].line[i][11];
	}
    }

    for (i = 0; i < proc[P_CPUINFO].lines; i++) {
	if (strncmp("physical id", proc[P_CPUINFO].line[i], 11) == 0) {
	    id = atoi(&proc[P_CPUINFO].line[i][14]);
	    if (id < 256)
		physicalcpu[id] = 1;
	}
    }
    for (i = 0; i < 256; i++)
	if (physicalcpu[i] == 1)
	    processorchips++;

    /* Start with index [1] as [0] contains overall CPU statistics */
    for (i = 0; i < proc[P_CPUINFO].lines; i++) {
	if (strncmp("siblings", proc[P_CPUINFO].line[i], 8) == 0) {
	    siblings = atoi(&proc[P_CPUINFO].line[i][11]);
	    break;
	}
    }
    for (i = 0; i < proc[P_CPUINFO].lines; i++) {
	if (strncmp("cpu cores", proc[P_CPUINFO].line[i], 9) == 0) {
	    cores = atoi(&proc[P_CPUINFO].line[i][12]);
	    break;
	}
    }
    if (siblings > cores)
	hyperthreads = siblings / cores;
    else
	hyperthreads = 0;
}
#endif

int stat8 = 0;			/* used to determine the number of variables on a cpu line in /proc/stat */
int stat10 = 0;			/* used to determine the number of variables on a cpu line in /proc/stat */


void proc_cpu()
{
    int i;
    int row;
    static int intr_line = 0;
    static int ctxt_line = 0;
    static int btime_line = 0;
    static int proc_line = 0;
    static int run_line = 0;
    static int block_line = 0;
    static int proc_cpu_first_time = 1;
    long long user;
    long long nice;
    long long sys;
    long long idle;
    long long iowait;
    long long hardirq;
    long long softirq;
    long long steal;
    long long guest;
    long long guest_nice;

    /* Only read data once per interval */
    if (proc_cpu_done == 1)
	return;

    /* If number of CPUs changed, then we need to find the index of intr_line, ... again */
    if (old_cpus != cpus)
	intr_line = 0;

    if (proc_cpu_first_time) {
	stat8 =
	    sscanf(&proc[P_STAT].line[0][5],
		   "%lld %lld %lld %lld %lld %lld %lld %lld", &user, &nice,
		   &sys, &idle, &iowait, &hardirq, &softirq, &steal);
	stat10 =
	    sscanf(&proc[P_STAT].line[0][5],
		   "%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld",
		   &user, &nice, &sys, &idle, &iowait, &hardirq, &softirq,
		   &steal, &guest, &guest_nice);
	proc_cpu_first_time = 0;
    }
    user = nice = sys = idle = iowait = hardirq = softirq = steal = guest =
	guest_nice = 0;
    if (stat10 == 10) {
	sscanf(&proc[P_STAT].line[0][5],
	       "%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld", &user,
	       &nice, &sys, &idle, &iowait, &hardirq, &softirq, &steal,
	       &guest, &guest_nice);
    } else {
	if (stat8 == 8) {
	    sscanf(&proc[P_STAT].line[0][5],
		   "%lld %lld %lld %lld %lld %lld %lld %lld", &user, &nice,
		   &sys, &idle, &iowait, &hardirq, &softirq, &steal);
	} else {		/* stat 4 variables here as older Linux proc */
	    sscanf(&proc[P_STAT].line[0][5], "%lld %lld %lld %lld",
		   &user, &nice, &sys, &idle);
	}
    }
    p->cpu_total.user = user;
    p->cpu_total.nice = nice;
    p->cpu_total.idle = idle;
    p->cpu_total.sys = sys;
    p->cpu_total.wait = iowait;	/* in the case of 4 variables = 0 */
    /* p->cpu_total.sys  = sys + hardirq + softirq + steal; */

    p->cpu_total.irq = hardirq;
    p->cpu_total.softirq = softirq;
    p->cpu_total.steal = steal;
    p->cpu_total.guest = guest;
    p->cpu_total.guest_nice = guest_nice;

#ifdef DEBUG
    if (debug)
	fprintf(stderr, "XX user=%lld wait=%lld sys=%lld idle=%lld\n",
		p->cpu_total.user,
		p->cpu_total.wait, p->cpu_total.sys, p->cpu_total.idle);
#endif /*DEBUG*/
	for (i = 0; i < cpus; i++) {
	user = nice = sys = idle = iowait = hardirq = softirq = steal = 0;

	/* allow for large CPU numbers */
	if (i + 1 > 1000)
	    row = 8;
	else if (i + 1 > 100)
	    row = 7;
	else if (i + 1 > 10)
	    row = 6;
	else
	    row = 5;

	if (stat10 == 10) {
	    sscanf(&proc[P_STAT].line[i + 1][row],
		   "%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld",
		   &user,
		   &nice,
		   &sys,
		   &idle,
		   &iowait,
		   &hardirq, &softirq, &steal, &guest, &guest_nice);

	} else if (stat8 == 8) {
	    sscanf(&proc[P_STAT].line[i + 1][row],
		   "%lld %lld %lld %lld %lld %lld %lld %lld",
		   &user,
		   &nice,
		   &sys, &idle, &iowait, &hardirq, &softirq, &steal);
	} else {
	    sscanf(&proc[P_STAT].line[i + 1][row], "%lld %lld %lld %lld",
		   &user, &nice, &sys, &idle);
	}
	p->cpuN[i].user = user;
	p->cpuN[i].nice = nice;
	p->cpuN[i].sys = sys;
	p->cpuN[i].idle = idle;
	p->cpuN[i].wait = iowait;
	p->cpuN[i].irq = hardirq;
	p->cpuN[i].softirq = softirq;
	p->cpuN[i].steal = steal;
	p->cpuN[i].guest = guest;
	p->cpuN[i].guest_nice = guest_nice;
    }

    if (intr_line == 0) {
	if (proc[P_STAT].line[i + 1][0] == 'p' &&
	    proc[P_STAT].line[i + 1][1] == 'a' &&
	    proc[P_STAT].line[i + 1][2] == 'g' &&
	    proc[P_STAT].line[i + 1][3] == 'e') {
	    /* 2.4 kernel */
	    intr_line = i + 3;
	    ctxt_line = i + 5;
	    btime_line = i + 6;
	    proc_line = i + 7;
	    run_line = i + 8;
	    block_line = i + 9;
	} else {
	    /* 2.6 kernel */
	    intr_line = i + 1;
	    ctxt_line = i + 2;
	    btime_line = i + 3;
	    proc_line = i + 4;
	    run_line = i + 5;
	    block_line = i + 6;
	}
    }
    p->cpu_total.intr = -1;
    p->cpu_total.ctxt = -1;
    p->cpu_total.procs = -1;
    p->cpu_total.running = -1;
    p->cpu_total.blocked = -1;
    if (proc[P_STAT].lines >= intr_line)
	sscanf(&proc[P_STAT].line[intr_line][0], "intr %lld",
	       &p->cpu_total.intr);
    if (proc[P_STAT].lines >= ctxt_line)
	sscanf(&proc[P_STAT].line[ctxt_line][0], "ctxt %lld",
	       &p->cpu_total.ctxt);
    if(boottime == 0) {
	struct tm ts;
	if (proc[P_STAT].lines >= btime_line)
	sscanf(&proc[P_STAT].line[btime_line][0], "btime %lld", &boottime);
	ts = *localtime((time_t *)&boottime);
	strftime (boottime_str, 64, "%I:%M %p %d-%b-%Y", &ts);
    }
    if (proc[P_STAT].lines >= proc_line)
	sscanf(&proc[P_STAT].line[proc_line][0], "processes %lld",
	       &p->cpu_total.procs);
    if (proc[P_STAT].lines >= run_line)
	sscanf(&proc[P_STAT].line[run_line][0], "procs_running %lld",
	       &p->cpu_total.running);
    if (proc[P_STAT].lines >= block_line)
	sscanf(&proc[P_STAT].line[block_line][0], "procs_blocked %lld",
	       &p->cpu_total.blocked);

    /* If we had a change in the number of CPUs, copy current interval data to the previous, so we
     * get a "0" utilization interval, but better than negative or 100%.
     * Heads-up - This effects POWER SMT changes too.
     */
    if (old_cpus != cpus) {
	memcpy((void *) &(q->cpu_total), (void *) &(p->cpu_total),
	       sizeof(struct cpu_stat));
	memcpy((void *) q->cpuN, (void *) p->cpuN,
	       sizeof(struct cpu_stat) * cpus);
    }

    /* Flag that we processed /proc/stat data; re-set in proc_read() when we re-read /proc/stat */
    proc_cpu_done = 1;
}

void proc_nfs()
{
    int i;
    int j;
    int len;
    int lineno;

/* sample /proc/net/rpc/nfs
net 0 0 0 0
rpc 70137 0 0
proc2 18 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
proc3 22 0 27364 0 32 828 22 40668 0 1 0 0 0 0 0 0 0 0 1212 6 2 1 0
proc4 35 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
*/
    if (proc[P_NFS].fp != 0) {
	for (lineno = 0; lineno < proc[P_NFS].lines; lineno++) {
	    if (!strncmp("proc2 ", proc[P_NFS].line[lineno], 6)) {
		/* client version 2 line readers "proc2 18 num num etc" */
		len = strlen(proc[P_NFS].line[lineno]);
		for (j = 0, i = 8; i < len && j < NFS_V2_NAMES_COUNT; i++) {
		    if (proc[P_NFS].line[lineno][i] == ' ') {
			p->nfs.v2c[j] =
			    atol(&proc[P_NFS].line[lineno][i + 1]);
			nfs_v2c_found = 1;
			j++;
		    }
		}
	    }
	    if (!strncmp("proc3 ", proc[P_NFS].line[lineno], 6)) {
		/* client version 3 line readers "proc3 22 num num etc" */
		len = strlen(proc[P_NFS].line[lineno]);
		for (j = 0, i = 8; i < len && j < NFS_V3_NAMES_COUNT; i++) {
		    if (proc[P_NFS].line[lineno][i] == ' ') {
			p->nfs.v3c[j] =
			    atol(&proc[P_NFS].line[lineno][i + 1]);
			nfs_v3c_found = 1;
			j++;
		    }
		}
	    }
	    if (!strncmp("proc4 ", proc[P_NFS].line[lineno], 6)) {
		/* client version 4 line readers "proc4 35 num num etc" */
		nfs_v4c_names_count = atoi(&proc[P_NFS].line[lineno][6]);
		len = strlen(proc[P_NFS].line[lineno]);
		for (j = 0, i = 8; i < len && j < nfs_v4c_names_count; i++) {
		    if (proc[P_NFS].line[lineno][i] == ' ') {
			p->nfs.v4c[j] =
			    atol(&proc[P_NFS].line[lineno][i + 1]);
			nfs_v4c_found = 1;
			j++;
		    }
		}
	    }
	}
    }
/* sample /proc/net/rpc/nfsd 
rc 0 0 0
fh 0 0 0 0 0
io 0 0
th 4 0 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000 0.000
ra 32 0 0 0 0 0 0 0 0 0 0 0
net 0 0 0 0
rpc 0 0 0 0 0
proc2 18 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
proc3 22 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
proc4 2 0 0
proc4ops 40 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
*/
    if (proc[P_NFSD].fp != 0) {
	for (lineno = 0; lineno < proc[P_NFSD].lines; lineno++) {
	    if (!strncmp("proc2 ", proc[P_NFSD].line[lineno], 6)) {
		/* server version 2 line readers "proc2 18 num num etc" */
		len = strlen(proc[P_NFSD].line[lineno]);
		for (j = 0, i = 8; i < len && j < NFS_V2_NAMES_COUNT; i++) {
		    if (proc[P_NFSD].line[lineno][i] == ' ') {
			p->nfs.v2s[j] =
			    atol(&proc[P_NFSD].line[lineno][i + 1]);
			nfs_v2s_found = 1;
			j++;
		    }
		}
	    }
	    if (!strncmp("proc3 ", proc[P_NFSD].line[lineno], 6)) {
		/* server version 3 line readers "proc3 22 num num etc" */
		len = strlen(proc[P_NFSD].line[lineno]);
		for (j = 0, i = 8; i < len && j < NFS_V2_NAMES_COUNT; i++) {
		    if (proc[P_NFSD].line[lineno][i] == ' ') {
			p->nfs.v3s[j] =
			    atol(&proc[P_NFSD].line[lineno][i + 1]);
			nfs_v3s_found = 1;
			j++;
		    }
		}
	    }
	    if (!strncmp("proc4ops ", proc[P_NFSD].line[lineno], 9)) {
		/* server version 4 line readers "proc4ops 40 num num etc"  
		   NOTE: the "ops" hence starting in column 9 */
		nfs_v4s_names_count = atol(&proc[P_NFSD].line[lineno][9]);
		len = strlen(proc[P_NFSD].line[lineno]);
		for (j = 0, i = 11; i < len && j < nfs_v4s_names_count;
		     i++) {
		    if (proc[P_NFSD].line[lineno][i] == ' ') {
			p->nfs.v4s[j] =
			    atol(&proc[P_NFSD].line[lineno][i + 1]);
			nfs_v4s_found = 1;
			j++;
		    }
		}
	    }
	}
    }
}

void proc_kernel()
{
    int i;
    p->cpu_total.uptime = 0.0;
    p->cpu_total.idletime = 0.0;
    p->cpu_total.uptime = atof(proc[P_UPTIME].line[0]);
    for (i = 0; i < strlen(proc[P_UPTIME].line[0]); i++) {
	if (proc[P_UPTIME].line[0][i] == ' ') {
	    p->cpu_total.idletime = atof(&proc[P_UPTIME].line[0][i + 1]);
	    break;
	}
    }

    sscanf(&proc[P_LOADAVG].line[0][0], "%f %f %f",
	   &p->cpu_total.mins1, &p->cpu_total.mins5, &p->cpu_total.mins15);

}

char *proc_find_sb(char *p)
{
    for (; *p != 0; p++)
	if (*p == ' ' && *(p + 1) == '(')
	    return p;
    return 0;
}

#define DISK_MODE_IO 1
#define DISK_MODE_DISKSTATS 2
#define DISK_MODE_PARTITIONS 3

int disk_mode = 0;

void proc_disk_io(double elapsed)
{
    int diskline;
    int i;
    int ret;
    char *str;
    int fudged_busy;

    disks = 0;
    for (diskline = 0; diskline < proc[P_STAT].lines; diskline++) {
	if (strncmp("disk_io", proc[P_STAT].line[diskline], 7) == 0)
	    break;
    }
    for (i = 8; i < strlen(proc[P_STAT].line[diskline]); i++) {
	if (proc[P_STAT].line[diskline][i] == ':')
	    disks++;
    }

    str = &proc[P_STAT].line[diskline][0];
    for (i = 0; i < disks; i++) {
	str = proc_find_sb(str);
	if (str == 0)
	    break;
	ret = sscanf(str, " (%d,%d):(%ld,%ld,%ld,%ld,%ld",
		     &p->dk[i].dk_major,
		     &p->dk[i].dk_minor,
		     &p->dk[i].dk_noinfo,
		     &p->dk[i].dk_reads,
		     &p->dk[i].dk_rkb,
		     &p->dk[i].dk_writes, &p->dk[i].dk_wkb);
	if (ret != 7)
	    exit(7);
	p->dk[i].dk_xfers = p->dk[i].dk_noinfo;
	/* blocks  are 512 bytes */
	p->dk[i].dk_rkb = p->dk[i].dk_rkb / 2;
	p->dk[i].dk_wkb = p->dk[i].dk_wkb / 2;

	p->dk[i].dk_bsize =
	    (p->dk[i].dk_rkb + p->dk[i].dk_wkb) / p->dk[i].dk_xfers * 1024;

	/* assume a disk does 200 op per second */
	fudged_busy = (p->dk[i].dk_reads + p->dk[i].dk_writes) / 2;
	if (fudged_busy > 100 * elapsed)
	    p->dk[i].dk_time += 100 * elapsed;
	p->dk[i].dk_time = fudged_busy;

	snprintf(p->dk[i].dk_name, 32, "dev-%d-%d", p->dk[i].dk_major,
		p->dk[i].dk_minor);
/*	fprintf(stderr,"disk=%d name=\"%s\" major=%d minor=%d\n", i,p->dk[i].dk_name, p->dk[i].dk_major,p->dk[i].dk_minor); */
	str++;
    }
}

void proc_diskstats(double elapsed)
{
    static FILE *fp = (FILE *) - 1;
    char buf[1024];
    int i;
    int ret;

    if (fp == (FILE *) - 1) {
	if ((fp = fopen("/proc/diskstats", "r")) == NULL) {
	    /* DEBUG if( (fp = fopen("diskstats","r")) == NULL) { */
	    error("failed to open - /proc/diskstats");
	    disks = 0;
	    return;
	}
    }
/*
   2    0 fd0 1 0 2 13491 0 0 0 0 0 13491 13491
   3    0 hda 41159 53633 1102978 620181 39342 67538 857108 4042631 0 289150 4668250
   3    1 hda1 58209 58218 0 0
   3    2 hda2 148 4794 10 20
   3    3 hda3 65 520 0 0
   3    4 hda4 35943 1036092 107136 857088
  22    0 hdc 167 5394 22308 32250 0 0 0 0 0 22671 32250 <-- USB !!
   8    0 sda 990 2325 4764 6860 9 3 12 417 0 6003 7277
   8    1 sda1 3264 4356 12 12
*/
    for (i = 0; i < DISKMAX;) {
	if (fgets(buf, 1024, fp) == NULL)
	    break;
	/* zero the data ready for reading */
	p->dk[i].dk_major =
	    p->dk[i].dk_minor =
	    p->dk[i].dk_name[0] =
	    p->dk[i].dk_reads =
	    p->dk[i].dk_rmerge =
	    p->dk[i].dk_rkb =
	    p->dk[i].dk_rmsec =
	    p->dk[i].dk_writes =
	    p->dk[i].dk_wmerge =
	    p->dk[i].dk_wkb =
	    p->dk[i].dk_wmsec =
	    p->dk[i].dk_inflight =
	    p->dk[i].dk_time = p->dk[i].dk_backlog = 0;

	ret =
	    sscanf(&buf[0],
		   "%d %d %s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu",
		   &p->dk[i].dk_major, &p->dk[i].dk_minor,
		   &p->dk[i].dk_name[0], &p->dk[i].dk_reads,
		   &p->dk[i].dk_rmerge, &p->dk[i].dk_rkb,
		   &p->dk[i].dk_rmsec, &p->dk[i].dk_writes,
		   &p->dk[i].dk_wmerge, &p->dk[i].dk_wkb,
		   &p->dk[i].dk_wmsec, &p->dk[i].dk_inflight,
		   &p->dk[i].dk_time, &p->dk[i].dk_backlog);
	if (ret == 7) {		/* shuffle the data around due to missing columns for partitions */
	    p->dk[i].dk_partition = 1;
	    p->dk[i].dk_wkb = p->dk[i].dk_rmsec;
	    p->dk[i].dk_writes = p->dk[i].dk_rkb;
	    p->dk[i].dk_rkb = p->dk[i].dk_rmerge;
	    p->dk[i].dk_rmsec = 0;
	    p->dk[i].dk_rmerge = 0;

	} else if (ret == 14)
	    p->dk[i].dk_partition = 0;
	else
	    fprintf(stderr,
		    "disk sscanf wanted 14 but returned=%d line=%s\n", ret,
		    buf);

	p->dk[i].dk_rkb /= 2;	/* sectors = 512 bytes */
	p->dk[i].dk_wkb /= 2;
	p->dk[i].dk_xfers = p->dk[i].dk_reads + p->dk[i].dk_writes;
	if (p->dk[i].dk_xfers == 0)
	    p->dk[i].dk_bsize = 0;
	else
	    p->dk[i].dk_bsize =
		((p->dk[i].dk_rkb +
		  p->dk[i].dk_wkb) / p->dk[i].dk_xfers) * 1024;

	p->dk[i].dk_time /= 10.0;	/* in milli-seconds to make it upto 100%, 1000/100 = 10 */

	if (p->dk[i].dk_xfers > 0)
	    i++;
    }
    if (reread) {
	fclose(fp);
	fp = (FILE *) - 1;
    } else
	rewind(fp);
    disks = i;
}

void strip_spaces(char *s)
{
    char *p;
    int spaced = 1;

    p = s;
    for (p = s; *p != 0; p++) {
	if (*p == ':')
	    *p = ' ';
	if (*p != ' ') {
	    *s = *p;
	    s++;
	    spaced = 0;
	} else if (spaced) {
	    /* do no thing as this is second space */
	} else {
	    *s = *p;
	    s++;
	    spaced = 1;
	}

    }
    *s = 0;
}

void proc_partitions(double elapsed)
{
    static FILE *fp = (FILE *) - 1;
    char buf[1024];
    int i = 0;
    int ret;

    if (fp == (FILE *) - 1) {
	if ((fp = fopen("/proc/partitions", "r")) == NULL) {
	    error("failed to open - /proc/partitions");
	    partitions = 0;
	    return;
	}
    }
    if (fgets(buf, 1024, fp) == NULL)
	goto end;		/* throw away the header lines */
    if (fgets(buf, 1024, fp) == NULL)
	goto end;
/*
major minor  #blocks  name     rio rmerge rsect ruse wio wmerge wsect wuse running use aveq

  33     0    1052352 hde 2855 15 2890 4760 0 0 0 0 -4 7902400 11345292
  33     1    1050304 hde1 2850 0 2850 3930 0 0 0 0 0 3930 3930
   3     0   39070080 hda 9287 19942 226517 90620 8434 25707 235554 425790 -12 7954830 33997658
   3     1   31744408 hda1 651 90 5297 2030 0 0 0 0 0 2030 2030
   3     2    6138720 hda2 7808 19561 218922 79430 7299 20529 222872 241980 0 59950 321410
   3     3     771120 hda3 13 41 168 80 0 0 0 0 0 80 80
   3     4          1 hda4 0 0 0 0 0 0 0 0 0 0 0
   3     5     408208 hda5 812 241 2106 9040 1135 5178 12682 183810 0 11230 192850
*/
    for (i = 0; i < DISKMAX; i++) {
	if (fgets(buf, 1024, fp) == NULL)
	    break;
	strip_spaces(buf);
	ret =
	    sscanf(&buf[0],
		   "%d %d %lu %s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu",
		   &p->dk[i].dk_major, &p->dk[i].dk_minor,
		   &p->dk[i].dk_blocks, (char *) &p->dk[i].dk_name,
		   &p->dk[i].dk_reads, &p->dk[i].dk_rmerge,
		   &p->dk[i].dk_rkb, &p->dk[i].dk_rmsec,
		   &p->dk[i].dk_writes, &p->dk[i].dk_wmerge,
		   &p->dk[i].dk_wkb, &p->dk[i].dk_wmsec,
		   &p->dk[i].dk_inflight, &p->dk[i].dk_use,
		   &p->dk[i].dk_aveq);
	p->dk[i].dk_rkb /= 2;	/* sectors = 512 bytes */
	p->dk[i].dk_wkb /= 2;
	p->dk[i].dk_xfers = p->dk[i].dk_rkb + p->dk[i].dk_wkb;
	if (p->dk[i].dk_xfers == 0)
	    p->dk[i].dk_bsize = 0;
	else
	    p->dk[i].dk_bsize =
		(p->dk[i].dk_rkb +
		 p->dk[i].dk_wkb) / p->dk[i].dk_xfers * 1024;

	p->dk[i].dk_time /= 10.0;	/* in milli-seconds to make it upto 100%, 1000/100 = 10 */

	if (ret != 15) {
#ifdef DEBUG
	    if (debug)
		fprintf(stderr, "sscanf wanted 15 returned = %d line=%s\n",
			ret, buf);
#endif	     /*DEBUG*/
		partitions_short = 1;
	} else
	    partitions_short = 0;
    }
  end:
    if (reread) {
	fclose(fp);
	fp = (FILE *) - 1;
    } else
	rewind(fp);
    disks = i;
}

void proc_disk(double elapsed)
{
    struct stat buf;
    int ret;
    if (disk_mode == 0) {
	ret = stat("/proc/diskstats", &buf);
	if (ret == 0) {
	    disk_mode = DISK_MODE_DISKSTATS;
	} else {
	    ret = stat("/proc/partitions", &buf);
	    if (ret == 0) {
		disk_mode = DISK_MODE_PARTITIONS;
	    } else {
		disk_mode = DISK_MODE_IO;
	    }
	}
    }
    switch (disk_mode) {
    case DISK_MODE_IO:
	proc_disk_io(elapsed);
	break;
    case DISK_MODE_DISKSTATS:
	proc_diskstats(elapsed);
	break;
    case DISK_MODE_PARTITIONS:
	proc_partitions(elapsed);
	break;
    }
}

#undef isdigit
#define isdigit(ch) ( ( '0' <= (ch)  &&  (ch) >= '9')? 0: 1 )

long proc_mem_search(char *s)
{
    int i;
    int j;
    int len;
    len = strlen(s);
    for (i = 0; i < proc[P_MEMINFO].lines; i++) {
	if (!strncmp(s, proc[P_MEMINFO].line[i], len)) {
	    for (j = len;
		 !isdigit(proc[P_MEMINFO].line[i][j]) &&
		 proc[P_MEMINFO].line[i][j] != 0; j++)
		/* do nothing */ ;
	    return atol(&proc[P_MEMINFO].line[i][j]);
	}
    }
    return -1;
}

void proc_mem()
{
    if (proc[P_MEMINFO].read_this_interval == 0)
	proc_read(P_MEMINFO);

    p->mem.memtotal = proc_mem_search("MemTotal");
    p->mem.memfree = proc_mem_search("MemFree");
    p->mem.memshared = proc_mem_search("MemShared");
    /* memshared was renamed (pointlessly) Sheme and includes RAM disks in later kernels */
    if(p->mem.memshared <= 0)
        p->mem.memshared = proc_mem_search("Shmem");

    p->mem.buffers = proc_mem_search("Buffers");
    p->mem.cached = proc_mem_search("Cached");
    p->mem.swapcached = proc_mem_search("SwapCached");
    p->mem.active = proc_mem_search("Active");
    p->mem.inactive = proc_mem_search("Inactive");
    p->mem.hightotal = proc_mem_search("HighTotal");
    p->mem.highfree = proc_mem_search("HighFree");
    p->mem.lowtotal = proc_mem_search("LowTotal");
    p->mem.lowfree = proc_mem_search("LowFree");
    p->mem.swaptotal = proc_mem_search("SwapTotal");
    p->mem.swapfree = proc_mem_search("SwapFree");
#ifndef SMALLMEM
    p->mem.dirty = proc_mem_search("Dirty");
    p->mem.writeback = proc_mem_search("Writeback");
    p->mem.mapped = proc_mem_search("Mapped");
    p->mem.slab = proc_mem_search("Slab");
    p->mem.committed_as = proc_mem_search("Committed_AS");
    p->mem.pagetables = proc_mem_search("PageTables");
    p->mem.hugetotal = proc_mem_search("HugePages_Total");
    p->mem.hugefree = proc_mem_search("HugePages_Free");
    p->mem.hugesize = proc_mem_search("Hugepagesize");
#else
    p->mem.bigfree = proc_mem_search("BigFree");
#endif /*SMALLMEM*/
}

#define MAX_SNAPS 72
#define MAX_SNAP_ROWS 20
#define SNAP_OFFSET 6

int next_cpu_snap = 0;
int cpu_snap_all = 0;

struct {
    double user;
    double kernel;
    double iowait;
    double idle;
    double steal;
} cpu_snap[MAX_SNAPS];

int snap_average()
{
    int i;
    int end;
    int total = 0;

    if (cpu_snap_all)
	end = MAX_SNAPS;
    else
	end = next_cpu_snap;

    for (i = 0; i < end; i++) {
	total = total + cpu_snap[i].user + cpu_snap[i].kernel;
    }
    return (total / end);
}

void snap_clear()
{
    int i;
    for (i = 0; i < MAX_SNAPS; i++) {
	cpu_snap[i].user = 0;
	cpu_snap[i].kernel = 0;
	cpu_snap[i].iowait = 0;
	cpu_snap[i].idle = 0;
	cpu_snap[i].steal = 0;
    }
    next_cpu_snap = 0;
    cpu_snap_all = 0;
}

void plot_snap(WINDOW * pad)
{
    int i;
    int j;
    double k;
    if (cursed) {
	mvwprintw(pad, 0, 0,
		  " CPU +---Long-Term-------------------------------------------------------------+");
	mvwprintw(pad, 1, 0, "100%%-|");
	mvwprintw(pad, 2, 1, "95%%-|");
	mvwprintw(pad, 3, 1, "90%%-|");
	mvwprintw(pad, 4, 1, "85%%-|");
	mvwprintw(pad, 5, 1, "80%%-|");
	mvwprintw(pad, 6, 1, "75%%-|");
	mvwprintw(pad, 7, 1, "70%%-|");
	mvwprintw(pad, 8, 1, "65%%-|");
	mvwprintw(pad, 9, 1, "60%%-|");
	mvwprintw(pad, 10, 1, "55%%-|");
	mvwprintw(pad, 11, 1, "50%%-|");
	mvwprintw(pad, 12, 1, "45%%-|");
	mvwprintw(pad, 13, 1, "40%%-|");
	mvwprintw(pad, 14, 1, "35%%-|");
	mvwprintw(pad, 15, 1, "30%%-|");
	mvwprintw(pad, 16, 1, "25%%-|");
	mvwprintw(pad, 17, 1, "20%%-|");
	mvwprintw(pad, 18, 1, "15%%-|");
	mvwprintw(pad, 19, 1, "10%%-|");
	mvwprintw(pad, 20, 1, " 5%%-|");

	mvwprintw(pad, 21, 4,
		  " +-------------------------------------------------------------------------+");
	if (colour) {
	    COLOUR wattrset(pad, COLOR_PAIR(2));
	    mvwprintw(pad, 0, 26, "User%%");
	    COLOUR wattrset(pad, COLOR_PAIR(1));
	    mvwprintw(pad, 0, 36, "System%%");
	    COLOUR wattrset(pad, COLOR_PAIR(4));
	    mvwprintw(pad, 0, 49, "Wait%%");
	    COLOUR wattrset(pad, COLOR_PAIR(5));
	    mvwprintw(pad, 0, 59, "Steal%%");
	    COLOUR wattrset(pad, COLOR_PAIR(0));
	}

	for (j = 0; j < MAX_SNAPS; j++) {
	    for (i = 0; i < MAX_SNAP_ROWS; i++) {
		wmove(pad, MAX_SNAP_ROWS - i, j + SNAP_OFFSET);
		if (cpu_snap[j].user + cpu_snap[j].kernel + cpu_snap[j].iowait + cpu_snap[j].idle + cpu_snap[j].steal == 0) {	/* if not all zeros */
		    COLOUR wattrset(pad, COLOR_PAIR(0));
		    wprintw(pad, " ");
		} else if ((cpu_snap[j].user / 100 * MAX_SNAP_ROWS) >
			   i + 0.5) {
		    COLOUR wattrset(pad, COLOR_PAIR(9));
		    wprintw(pad, "U");
		} else if ((cpu_snap[j].user + cpu_snap[j].kernel) / 100 *
			   MAX_SNAP_ROWS > i + 0.5) {
		    COLOUR wattrset(pad, COLOR_PAIR(8));
		    wprintw(pad, "s");
		} else
		    if ((cpu_snap[j].user + cpu_snap[j].kernel +
			 cpu_snap[j].iowait) / 100 * MAX_SNAP_ROWS >
			i + 0.5) {
		    COLOUR wattrset(pad, COLOR_PAIR(10));
		    wprintw(pad, "w");
		} else if ((cpu_snap[j].user + cpu_snap[j].kernel + cpu_snap[j].iowait + cpu_snap[j].idle) / 100 * MAX_SNAP_ROWS > i) {	/*no +0.5 or too few Steal's */
		    COLOUR wattrset(pad, COLOR_PAIR(0));
		    wprintw(pad, " ");
		} else if (cpu_snap[j].user + cpu_snap[j].kernel + cpu_snap[j].iowait + cpu_snap[j].idle + cpu_snap[j].steal > i) {	/* if not all zeros */
		    COLOUR wattrset(pad, COLOR_PAIR(5));
		    wprintw(pad, "S");
		}
	    }
	    k = cpu_snap[j].user + cpu_snap[j].kernel + cpu_snap[j].iowait;
	    if (0.1 < k && k < 5.0) {	/*  not zero but less than 5% */
		wmove(pad, MAX_SNAP_ROWS, j + SNAP_OFFSET);
		COLOUR wattrset(pad, COLOR_PAIR(2));
		wprintw(pad, "_");
	    }
	}
	COLOUR wattrset(pad, COLOR_PAIR(0));
	for (i = 0; i < MAX_SNAP_ROWS; i++) {
	    wmove(pad, MAX_SNAP_ROWS - i, next_cpu_snap + SNAP_OFFSET);
	    wprintw(pad, "|");
	}
	wmove(pad, MAX_SNAP_ROWS + 1 - (snap_average() / 5),
	      next_cpu_snap + SNAP_OFFSET);
	wprintw(pad, "+");
	if (dotline) {
	    for (i = 0; i < MAX_SNAPS; i++) {
		wmove(pad, MAX_SNAP_ROWS + 1 - dotline * 2,
		      i + SNAP_OFFSET);
		wprintw(pad, "+");
	    }
	    dotline = 0;
	}
    }
}

/* This saves the CPU overall usage for later ploting on the screen */
void save_snap(double user, double kernel, double iowait, double idle,
	       double steal)
{
    cpu_snap[next_cpu_snap].user = user;
    cpu_snap[next_cpu_snap].kernel = kernel;
    cpu_snap[next_cpu_snap].iowait = iowait;
    cpu_snap[next_cpu_snap].idle = idle;
    cpu_snap[next_cpu_snap].steal = steal;
    next_cpu_snap++;
    if (next_cpu_snap >= MAX_SNAPS) {
	next_cpu_snap = 0;
	cpu_snap_all = 1;
    }
}

void plot_smp(WINDOW * pad, int cpu_no, int row, double user,
	      double kernel, double iowait, double idle, double steal)
{
    int i;
    int peak_col;

    if (show_rrd)
	return;

    if (cpu_peak[cpu_no] < (user + kernel + iowait))
	cpu_peak[cpu_no] =
	    (double) ((int) user / 2 + (int) kernel / 2 +
		      (int) iowait / 2) * 2.0;

    if (cursed) {
	if (cpu_no == 0)
	    mvwprintw(pad, row, 0, "Avg");
	else
	    mvwprintw(pad, row, 0, "%3d", cpu_no);
	mvwprintw(pad, row, 3, "% 6.1lf", user);
	mvwprintw(pad, row, 9, "% 6.1lf", kernel);
	mvwprintw(pad, row, 15, "% 6.1lf", iowait);
	if (steal) {
	    mvwprintw(pad, row, 21, "% 6.1lf", steal);
	} else {
	    mvwprintw(pad, row, 21, "% 6.1lf", idle);
	}
	mvwprintw(pad, row, 27, "|");
	wmove(pad, row, 28);
	for (i = 0; i < (int) (user / 2); i++) {
	    COLOUR wattrset(pad, COLOR_PAIR(9));
	    wprintw(pad, "U");
	}
	for (i = 0; i < (int) (kernel / 2); i++) {
	    COLOUR wattrset(pad, COLOR_PAIR(8));
	    wprintw(pad, "s");
	}
	for (i = 0; i < (int) (iowait / 2); i++) {
	    COLOUR wattrset(pad, COLOR_PAIR(10));
	    wprintw(pad, "W");
	}
	COLOUR wattrset(pad, COLOR_PAIR(0));
	for (i = 0; i <= (int) (idle / 2); i++) {	/* added "=" to try to conteract missing halves */
#ifdef POWER
	    if (lparcfg.smt_mode > 1
		&& ((cpu_no - 1) % lparcfg.smt_mode) == 0 && (i % 2))
		wprintw(pad, ".");
	    else
#endif
		wprintw(pad, " ");
	}
	for (i = 0; i < (int) ((steal + 1) / 2); i++) {
	    COLOUR wattrset(pad, COLOR_PAIR(5));
	    wprintw(pad, "S");
	}
	COLOUR wattrset(pad, COLOR_PAIR(0));
	mvwprintw(pad, row, 77, "| ");

	peak_col = 28 + (int) (cpu_peak[cpu_no] / 2);
	if (peak_col > 77)
	    peak_col = 77;
	mvwprintw(pad, row, peak_col, ">");
    } else {
	/* Sanity check the numnbers */
	if (user < 0.0 || kernel < 0.0 || iowait < 0.0 || idle < 0.0
	    || idle > 100.0 || steal < 0) {
	    user = kernel = iowait = idle = steal = 0;
	}

	if (first_steal && steal > 0) {
	    fprintf(fp, "AAA,steal,1\n");
	    first_steal = 0;
	}
	if (cpu_no == 0)
	    fprintf(fp, "CPU_ALL,%s,%.1lf,%.1lf,%.1lf,%.1f,%.1lf,,%d\n",
		    LOOP, user, kernel, iowait, idle, steal, cpus);
	else {
	    fprintf(fp, "CPU%03d,%s,%.1lf,%.1lf,%.1lf,%.1lf,%.1f\n",
		    cpu_no, LOOP, user, kernel, iowait, idle, steal);
	}
    }
}

/* Added variable to remember started children
 * 0 - start
 * 1 - snap
 * 2 - end
*/
#define CHLD_START 0
#define CHLD_SNAP 1
#define CHLD_END 2
int nmon_children[3] = { -1, -1, -1 };

void init_pairs()
{
    COLOUR init_pair((short) 0, (short) 7, (short) 0);	/* White */
    COLOUR init_pair((short) 1, (short) 1, (short) 0);	/* Red */
    COLOUR init_pair((short) 2, (short) 2, (short) 0);	/* Green */
    COLOUR init_pair((short) 3, (short) 3, (short) 0);	/* Yellow */
    COLOUR init_pair((short) 4, (short) 4, (short) 0);	/* Blue */
    COLOUR init_pair((short) 5, (short) 5, (short) 0);	/* Magenta */
    COLOUR init_pair((short) 6, (short) 6, (short) 0);	/* Cyan */
    COLOUR init_pair((short) 7, (short) 7, (short) 0);	/* White */
    COLOUR init_pair((short) 8, (short) 0, (short) 1);	/* Red background, red text */
    COLOUR init_pair((short) 9, (short) 0, (short) 2);	/* Green background, green text */
    COLOUR init_pair((short) 10, (short) 0, (short) 4);	/* Blue background, blue text */
    COLOUR init_pair((short) 11, (short) 0, (short) 3);	/* Yellow background, yellow text */
    COLOUR init_pair((short) 12, (short) 0, (short) 6);	/* Cyan background, cyan text */
}

/* Signal handler 
 * SIGUSR1 or 2 is used to stop nmon cleanly
 * SIGWINCH is used when the window size is changed
 */
void interrupt(int signum)
{
    int child_pid;
    int waitstatus;
    if (signum == SIGCHLD) {
	while ((child_pid = waitpid(0, &waitstatus, 0)) == -1) {
	    if (errno == EINTR)	/* retry */
		continue;
	    return;		/* ECHLD, EFAULT */
	}
	if (child_pid == nmon_children[CHLD_SNAP])
	    nmon_children[CHLD_SNAP] = -1;
	signal(SIGCHLD, interrupt);
	return;
    }
    if (signum == SIGUSR1 || signum == SIGUSR2) {
	maxloops = loop;
	return;
    }
    if (signum == SIGWINCH) {
	CURSE endwin();		/* stop + start curses so it works out the # of row and cols */
	CURSE initscr();
	CURSE cbreak();
	signal(SIGWINCH, interrupt);
	COLOUR colour = has_colors();
	COLOUR start_color();
	COLOUR init_pairs();
	CURSE clear();
	return;
    }
    CURSE endwin();
    exit(0);
}


/* only place the q=previous and p=currect pointers are modified */
void switcher(void)
{
    static int which = 1;
    int i;

    if (which) {
	p = &database[0];
	q = &database[1];
	which = 0;
    } else {
	p = &database[1];
	q = &database[0];
	which = 1;
    }
    if (flash_on)
	flash_on = 0;
    else
	flash_on = 1;

    /* Reset flags so /proc/... is re-read in next interval */
    for (i = 0; i < P_NUMBER; i++) {
	proc[i].read_this_interval = 0;
    }
#ifdef POWER
    lparcfg_processed = 0;
#endif
}


/* Lookup the right string */
char *status(int n)
{
    switch (n) {
    case 0:
	return "Run  ";
    default:
	return "Sleep";
    }
}

/* Lookup the right process state string */
char *get_state(char n)
{
    static char duff[64];
    switch (n) {
    case 'R':
	return "Running  ";
    case 'S':
	return "Sleeping ";
    case 'D':
	return "DiskSleep";
    case 'Z':
	return "Zombie   ";
    case 'T':
	return "Traced   ";
    case 'W':
	return "Paging   ";
    default:
	snprintf(duff, 64, "%d", n);
	return duff;
    }
}

/* User Defined Disk Groups */
char *save_word(char *in, char *out)
{
    int len;
    int i;
    len = strlen(in);
    out[0] = 0;
    for (i = 0; i < len; i++) {
	if (isalnum(in[i]) || in[i] == '_' || in[i] == '-' || in[i] == '/') {
	    out[i] = in[i];
	    out[i + 1] = 0;
	} else
	    break;
    }
    for (; i < len; i++)
	if (isalnum(in[i]))
	    return &in[i];
    return &in[i];
}

#define DGROUPS 64
#define DGROUPITEMS 512

char *dgroup_filename;
char *dgroup_name[DGROUPS];
int *dgroup_data;
int dgroup_disks[DGROUPS];
int dgroup_total_disks = 0;
int dgroup_total_groups;

void load_dgroup(struct dsk_stat *dk)
{
    FILE *gp;
    char line[4096];
    char name[1024];
    int i, j;
    char *nextp;

    if (dgroup_loaded == 2)
	return;
    dgroup_data = MALLOC(sizeof(int) * DGROUPS * DGROUPITEMS);
    for (i = 0; i < DGROUPS; i++)
	for (j = 0; j < DGROUPITEMS; j++)
	    dgroup_data[i * DGROUPITEMS + j] = -1;

    gp = fopen(dgroup_filename, "r");

    if (gp == NULL) {
	perror("opening disk group file");
	fprintf(stderr, "ERROR: failed to open %s\n", dgroup_filename);
	exit(9);
    }

    for (dgroup_total_groups = 0;
	 fgets(line, 4096 - 1, gp) != NULL
	 && dgroup_total_groups < DGROUPS; dgroup_total_groups++) {
	/* ignore lines starting with # */
	if (line[0] == '#') {	/* was a comment line */
	    /* Decrement dgroup_total_groups by 1 to correct index for next loop */
	    --dgroup_total_groups;
	    continue;
	}
	/* save the name */
	nextp = save_word(line, name);
	if (strlen(name) == 0) {	/* was a blank line */
	    fprintf(stderr,
		    "ERROR nmon:ignoring odd line in diskgroup file \"%s\"\n",
		    line);
	    /* Decrement dgroup_total_groups by 1 to correct index for next loop */
	    --dgroup_total_groups;
	    continue;
	}
	/* Added +1 to be able to correctly store the terminating \0 character */
	dgroup_name[dgroup_total_groups] = MALLOC(strlen(name) + 1);
	strcpy(dgroup_name[dgroup_total_groups], name);

	/* save the hdisks */
	for (i = 0; i < DGROUPITEMS && *nextp != 0; i++) {
	    nextp = save_word(nextp, name);
	    for (j = 0; j < disks; j++) {
		if (strcmp(dk[j].dk_name, name) == 0) {
		    /*DEBUG printf("DGadd group=%s,name=%s,disk=%s,dgroup_total_groups=%d,dgroup_total_disks=%d,j=%d,i=%d,index=%d.\n",
		       dgroup_name[dgroup_total_groups], 
		       name, dk[j].dk_name, dgroup_total_groups, dgroup_total_disks, j, i,dgroup_total_groups*DGROUPITEMS+i);
		     */
		    dgroup_data[dgroup_total_groups * DGROUPITEMS + i] = j;
		    dgroup_disks[dgroup_total_groups]++;
		    dgroup_total_disks++;
		    break;
		}
	    }
	    if (j == disks)
		fprintf(stderr,
			"ERROR nmon:diskgroup file - failed to find disk=%s for group=%s disks known=%d\n",
			name, dgroup_name[dgroup_total_groups], disks);
	}
    }
    fclose(gp);
    dgroup_loaded = 2;
}


void list_dgroup(struct dsk_stat *dk)
{
    int i, j, k, n;
    int first = 1;

    /* DEBUG for (n = 0, i = 0; i < dgroup_total_groups; i++) {
       fprintf(fp, "CCCG,%03d,%s", n++, dgroup_name[i]);
       for (j = 0; j < dgroup_disks[i]; j++) {
       if (dgroup_data[i*DGROUPITEMS+j] != -1) {
       fprintf(fp, ",%d=%d", j, dgroup_data[i*DGROUPITEMS+j]);
       }
       }
       fprintf(fp, "\n");
       }
     */
    if (!show_dgroup)
	return;

    for (n = 0, i = 0; i < dgroup_total_groups; i++) {
	if (first) {
	    fprintf(fp, "BBBG,%03d,User Defined Disk Groups Name,Disks\n",
		    n++);
	    first = 0;
	}
	fprintf(fp, "BBBG,%03d,%s", n++, dgroup_name[i]);
	for (k = 0, j = 0; j < dgroup_disks[i]; j++) {
	    if (dgroup_data[i * DGROUPITEMS + j] != -1) {
		fprintf(fp, ",%s",
			dk[dgroup_data[i * DGROUPITEMS + j]].dk_name);
		k++;
	    }
	    /* add extra line if we have lots to stop spreadsheet line width problems */
	    if (k == 128) {
		fprintf(fp, "\nBBBG,%03d,%s continued", n++,
			dgroup_name[i]);
	    }
	}
	fprintf(fp, "\n");
    }
    fprintf(fp, "DGBUSY,Disk Group Busy %s", hostname);
    for (i = 0; i < DGROUPS; i++) {
	if (dgroup_name[i] != 0)
	    fprintf(fp, ",%s", dgroup_name[i]);
    }
    fprintf(fp, "\n");
    fprintf(fp, "DGREAD,Disk Group Read KB/s %s", hostname);
    for (i = 0; i < DGROUPS; i++) {
	if (dgroup_name[i] != 0)
	    fprintf(fp, ",%s", dgroup_name[i]);
    }
    fprintf(fp, "\n");
    fprintf(fp, "DGWRITE,Disk Group Write KB/s %s", hostname);
    for (i = 0; i < DGROUPS; i++) {
	if (dgroup_name[i] != 0)
	    fprintf(fp, ",%s", dgroup_name[i]);
    }
    fprintf(fp, "\n");
    fprintf(fp, "DGSIZE,Disk Group Block Size KB %s", hostname);
    for (i = 0; i < DGROUPS; i++) {
	if (dgroup_name[i] != 0)
	    fprintf(fp, ",%s", dgroup_name[i]);
    }
    fprintf(fp, "\n");
    fprintf(fp, "DGXFER,Disk Group Transfers/s %s", hostname);
    for (i = 0; i < DGROUPS; i++) {
	if (dgroup_name[i] != 0)
	    fprintf(fp, ",%s", dgroup_name[i]);
    }
    fprintf(fp, "\n");

    /* If requested provide additional data available in /proc/diskstats */
    if (extended_disk == 1 && disk_mode == DISK_MODE_DISKSTATS) {
	fprintf(fp, "DGREADS,Disk Group read/s %s", hostname);
	for (i = 0; i < DGROUPS; i++) {
	    if (dgroup_name[i] != 0)
		fprintf(fp, ",%s", dgroup_name[i]);
	}
	fprintf(fp, "\n");
	fprintf(fp, "DGREADMERGE,Disk Group merged read/s %s", hostname);
	for (i = 0; i < DGROUPS; i++) {
	    if (dgroup_name[i] != 0)
		fprintf(fp, ",%s", dgroup_name[i]);
	}
	fprintf(fp, "\n");
	fprintf(fp, "DGREADSERV,Disk Group read service time (SUM ms) %s",
		hostname);
	for (i = 0; i < DGROUPS; i++) {
	    if (dgroup_name[i] != 0)
		fprintf(fp, ",%s", dgroup_name[i]);
	}
	fprintf(fp, "\n");
	fprintf(fp, "DGWRITES,Disk Group write/s %s", hostname);
	for (i = 0; i < DGROUPS; i++) {
	    if (dgroup_name[i] != 0)
		fprintf(fp, ",%s", dgroup_name[i]);
	}
	fprintf(fp, "\n");
	fprintf(fp, "DGWRITEMERGE,Disk Group merged write/s %s", hostname);
	for (i = 0; i < DGROUPS; i++) {
	    if (dgroup_name[i] != 0)
		fprintf(fp, ",%s", dgroup_name[i]);
	}
	fprintf(fp, "\n");
	fprintf(fp,
		"DGWRITESERV,Disk Group write service time (SUM ms) %s",
		hostname);
	for (i = 0; i < DGROUPS; i++) {
	    if (dgroup_name[i] != 0)
		fprintf(fp, ",%s", dgroup_name[i]);
	}
	fprintf(fp, "\n");
	fprintf(fp, "DGINFLIGHT,Disk Group in flight IO %s", hostname);
	for (i = 0; i < DGROUPS; i++) {
	    if (dgroup_name[i] != 0)
		fprintf(fp, ",%s", dgroup_name[i]);
	}
	fprintf(fp, "\n");
	fprintf(fp, "DGBACKLOG,Disk Group Backlog time (ms) %s", hostname);
	for (i = 0; i < DGROUPS; i++) {
	    if (dgroup_name[i] != 0)
		fprintf(fp, ",%s", dgroup_name[i]);
	}
	fprintf(fp, "\n");
    }
}

int is_dgroup_name(char *name)
{
    int i;
    for (i = 0; i < DGROUPS; i++) {
	if (dgroup_name[i] == (char *) 0)
	    return 0;
	if (strncmp(name, dgroup_name[i], strlen(name)) == 0)
	    return 1;
    }
    return 0;
}



void hint(void)
{
    printf("Hint for %s version %s\n", progname, VERSION);
    printf("\tFull Help Info : %s -h\n\n", progname);
    printf("\tOn-screen Stats: %s\n", progname);
    printf
	("\tData Collection: %s -f [-s <seconds>] [-c <count>] [-t|-T]\n",
	 progname);
    printf("\tCapacity Plan  : %s -x\n", progname);
    printf("Interactive-Mode:\n");
    printf
	("\tRead the Welcome screen & at any time type: \"h\" for more help\n");
    printf("\tType \"q\" to exit nmon\n\n");
    printf("For Data-Collect-Mode\n");
    printf
	("\t-f            Must be the first option on the line (switches off interactive mode)\n");
    printf
	("\t              Saves data to a CSV Spreadsheet format .nmon file in then local directory\n");
    printf
	("\t              Note: -f sets a defaults -s300 -c288    which you can then modify\n");
    printf("\tFurther Data Collection Options:\n");
    printf("\t-s <seconds>  time between data snapshots\n");
    printf("\t-c <count>    of snapshots before exiting\n");
    printf
	("\t-t            Includes Top Processes stats (-T also collects command arguments)\n");
    printf
	("\t-x            Capacity Planning=15 min snapshots for 1 day. (nmon -ft -s 900 -c 96)\n");
    printf("---- End of Hints\n");
}

void help(void)
{
    hint();
    printf("---- Full Help Information for %s\n\n", SccsId);
    printf("For Interactive and Data Collection Mode:\n");
    printf("\tUser Defined Disk Groups (DG) - This works in both modes\n");
    printf ("\tIt is a work around Linux issues, where disks & partitions are mixed up in /proc files\n");
    printf ("\t& drive driver developers use bizarre device names, making it trick to separate them.\n");
    printf("\t-g <filename> Use this file to define the groups\n");
    printf ("\t              - On each line: group-name <disks-list>   (space separated list)\n");
    printf("\t              - Example line: database sdb sdc sdd sde\n");
    printf("\t              - Up to 64 disk groups, 512 disks per line\n");
    printf ("\t              - Disks names can appear more than one group\n");
    printf ("\t-g auto       - Will generate a file called \"auto\" with just disks from \"lsblk|grep disk\" output\n");
    printf("\t For Interactive use define the groups then type: g or G\n");
    printf ("\t For Data Capture defining the groups switches on data collection\n");
    printf("\n");
    printf ("Data-Collect-Mode = spreadsheet format (i.e. comma separated values)\n");
    printf ("\tNote: Use only one of f, F, R, x, X or z to switch on Data Collection mode\n");
    printf ("\tNote: Make it the first argument then use other options to modify the defaults\n");
    printf ("\tNote: Don't collect data that you don't want - it just makes the files too large\n");
    printf ("\tNote: Too many snapshots = too much data and crashes Analyser and other tools\n");
    printf ("\tNote: 500 to 800 snapshots make a good graph on a normal size screen\n");
    printf ("\tRecommended normal minimal options: snapshots every 2 minutes all day: \n");
    printf("\t\tSimple capture:      nmon -f  -s 120 -c 720\n");
    printf("\t\tWith Top Procs:      nmon -fT -s 120 -c 720\n");
    printf ("\t\tSet the directory:   nmon -fT -s 120 -c 720 -m /home/nag/nmon\n");
    printf
	("\t\tCapture a busy hour: nmon -fT -s   5 -c 720 -m /home/nag/nmon\n");
    printf("\n");
    printf("For Data-Collect-Mode Options\n");
    printf
	("\t-f            spreadsheet output format [note: default -s300 -c288]\n");
    printf("\t\t\t output file is <hostname>_YYYYMMDD_HHMM.nmon\n");
    printf("\t-F <filename> same as -f but user supplied filename\n");
    printf("\t\t\t Not recommended as the default file name is perfect\n");
    printf("\tThe other options in alphabetical order:\n");
    printf("\t-a            Include Accelerator GPU stats\n");
    printf
	("\t-b            Online only: for black and white mode (switch off colour)\n");
    printf("\t-c <number>   The number of snapshots before nmon stops\n");
    printf
	("\t-d <disks>    To set the maximum number of disks [default 256]\n");
    printf
	("\t              Ignores disks if the systems has 100's of disk or the config is odd!\n");
    printf
	("\t-D            Use with -g to add the Disk Wait/Service Time & in-flight stats\n");
    printf("\t-f and -F     See above\n");
    printf
	("\t-g <filename> User Defined Disk Groups (see above) - Data Capture: Generates  BBBG & DG lines\n");
    printf
	("\t-g auto       See above but makes the file \"auto\" for you of just the disks like sda etc.\n");
    printf("\t-h            This help output\n");
    printf
	("\t-I <percent>  Set the ignore process & disks busy threshold (default 0.1%%)\n");
    printf
	("\t              Don't save or show proc/disk using less than this percent\n");
    printf
	("\t-J            Switch-off Journel Filesystem stats collection (can causes issues with automound NFS)\n");
    printf
	("\t-l <dpl>      Disks per line in data capture to avoid spreadsheet width issues. Default 150. EMC=64.\n");
    printf
	("\t-m <directory> nmon changes to this directory before saving to file\n");
    printf("\t              Useful when starting nmon via cron\n");
    printf
	("\t-M 		Adds MHz stats for each CPU thread. Some POWER8 model CPU cores can be different frequencies\n");
    printf
	("\t-N            Include NFS Network File System for V2, V3 and V4\n");
    printf
	("\t-p            nmon outputs the PID when it starts. Useful in scripts to capture the PID for a later safe stop.\n");
    printf
	("\t-r <runname>  Use in a benchmark to record the run details for later analysis [default hostname]\n");
    printf
	("\t-R  		Old rrdtool format used by some - may be removed in the future. If you use this email Nigel\n");
    printf
	("\t-s <seconds>  Time between snap shots - with \"-c count\" decides duration of the data capture\n");
    printf("\t-t            Include Top Processes in the output\n");
    printf
	("\t-T            As -t plus it saves command line arguments in UARG section\n");
    printf
	("\t-U            Include the Linux 10 CPU utilisation stats (CPUUTIL lines in the file)\n");
    printf("\t-V            Print nmon version & exit immediately\n");
    printf("\n");
    printf("\tTo manually load nmon files into a spreadsheet:\n");
    printf("\t\tsort -A *nmon >stats.csv\n");
    printf("\t\tTransfer the stats.csv file to your PC\n");
    printf
	("\t\tStart spreadsheet & then Open with type=comma-separated-value ASCII file\n");
    printf("\t\tThis puts every datum in a different cell\n");
    printf
	("\t\tNow select the data of one type (same 1st column) and graph it\n");
    printf
	("\t\tThe nmon Analyser & other tools do not need the file sorted.\n");
    printf("\n");
    printf("Capacity Planning mode - use cron to run each day\n");
    printf("\t-x            Sensible spreadsheet output for one day\n");
    printf
	("\t              Every 15 mins for 1 day ( i.e. -ft -s 900 -c 96)\n");
    printf("\t-X            Sensible spreadsheet output for busy hour\n");
    printf
	("\t              Every 30 secs for 1 hour ( i.e. -ft -s 30 -c 120)\n");
    printf
	("\t-z            Like -x but the output saved in /var/perf/tmp assuming root user\n");
    printf("\n");

    printf("Interactive Mode Keys in Alphabetical Order\n");
    printf
	("    Start nmon then type the letters below to switch on & off particular stats\n");
    printf("    The stats are always in the same order on-screen\n");
    printf
	("    To see more stats: make the font smaller or use two windows\n\n");
    printf("\tKey --- Toggles on off to control what is displayed ---\n");
#ifdef NVIDIA_GPU
    printf("\ta   = Accelerator from Nvidia GPUs\n");
#endif				/*NVIDIA_GPU */
    printf
	("\tb   = Black and white mode (or use -b command line option)\n");
    printf
	("\tc   = CPU Utilisation stats with bar graphs (CPU core threads)\n");
    printf
	("\tC   = CPU Utilisation as above but concise wide view (up to 192 CPUs)\n");
    printf("\td   = Disk I/O Busy%% & Graphs of Read and Write KB/s\n");
    printf
	("\tD   = Disk I/O Numbers including Transfers, Average Block Size & Peaks (type: 0 to reset)\n");
    printf
	("\tg   = User Defined Disk Groups            (assumes -g <file> when starting nmon)\n");
    printf
	("\tG   = Change Disk stats (d) to just disks (assumes -g auto   when starting nmon)\n");
    printf("\th   = This help information\n");
    printf("\tj   = File Systems including Journal File Systems\n");
    printf("\tJ   =  Reduces \"j\" output by removing unreal File Systems\n");
    printf
	("\tk   = Kernel stats Run Queue, context-switch, fork, Load Average & Uptime\n");
    printf
	("\tl   = Long term Total CPU (over 75 snapshots) via bar graphs\n");
    printf("\tL   = Large and =Huge memory page stats\n");
    printf("\tm   = Memory & Swap stats\n");
    printf
	("\tM   = MHz for machines with variable frequency 1st=Threads 2nd=Cores 3=Graphs\n");
    printf
	("\tn   = Network stats & errors (if no errors it disappears)\n");
    printf("\tN   = NFS - Network File System\n");
    printf("\t      1st NFS V2 & V3, 2nd=NFS4-Client & 3rd=NFS4-Server\n");
    printf
	("\to   = Disk I/O Map (one character per disk pixels showing how busy it is)\n");
    printf("\t      Particularly good if you have 100's of disks \n");
#ifdef PARTITIONS
    printf("\tP   = Partitions Disk I/O Stats\n");
#endif
#ifdef POWER
    printf("\tp   = PowerVM LPAR Stats from /proc/ppc64/lparcfg\n");
#endif
    printf("\tq   = Quit\n");
    printf
	("\tr   = Resources: Machine type, name, cache details & OS version & Distro + LPAR\n");
    printf
	("\tt   = Top Processes: select the data & order 1=Basic, 3=Perf 4=Size 5=I/O=root only\n");
    printf("\tu   = Top Process with command line details\n");
    printf("\tU   = CPU utilisation stats - all 10 Linux stats:\n");
    printf
	("\t      user, user_nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice\n");
    printf
	("\tv   = Experimental Verbose mode - tries to make recommendations\n");
    printf("\tV   = Virtual Memory stats\n");
    printf("\n");
    printf("\tKey --- Other Interactive Controls ---\n");
    printf("\t+   = Double the screen refresh time\n");
    printf("\t-   = Halves the screen refresh time\n");
    printf
	("\t0   = Reset peak counts to zero (peak highlight with \">\")\n");
    printf("\t1   = Top Processes mode 1 Nice, Priority, Status\n");
    printf("\t3   = Top Processes mode 3 CPU, Memory, Faults\n");
    printf("\t4   = Top Processes mode 4 as 3 but order by memory\n");
    printf
	("\t5   = Top Processes mode 5 as 3 but order by I/O (if root user)\n");
    printf("\t6   = Highlights 60%% row on Long Term CPU view\n");
    printf("\t7   = Highlights 70%% row on Long Term CPU view\n");
    printf("\t8   = Highlights 80%% row on Long Term CPU view\n");
    printf("\t9   = Highlights 90%% row on Long Term CPU view\n");
    printf
	("\t.   = Minimum mode i.e. only busy disks and processes shown\n");
    printf("\tspace = Refresh screen now\n");

    printf("\n");
    printf("Interactive Start-up Control\n");
    printf
	("\tIf you find you always type the same toggles every time you start\n");
    printf("\tthen place them in the NMON shell variable. For example:\n");
    printf("\t export NMON=cmdrtn\n");

    printf("\n");
    printf("Other items for Interactive and Data Collection mode:\n");
    printf
	("\ta) To limit the processes nmon lists (online and to a file)\n");
    printf
	("\t    either set NMONCMD0 to NMONCMD63 to the program names\n");
    printf("\t    or use -C cmd:cmd:cmd etc. example: -C ksh:vi:syncd\n");
    printf("Other items for Data Collection mode:\n");
    printf("\tb) To you want to stop nmon use: kill -USR2 <nmon-pid>\n");
    printf("\tc) Use -p and nmon outputs the background process pid\n");
    printf
	("\td) If you want to pipe nmon output to other commands use a FIFO:\n");
    printf("\t    mkfifo /tmp/mypipe\n");
    printf("\t    nmon -F /tmp/mypipe &\n");
    printf("\t    tail -f /tmp/mypipe\n");
    printf("\te) If nmon fails please report it with:\n");
    printf("\t   1) nmon version like: %s\n", VERSION);
    printf
	("\t   2) the output of: cd /proc; cat cpuinfo meminfo partitions stat vmstat\n");
    printf("\t   3) some clue of what you were doing\n");
    printf
	("\t   4) I may ask you to run the debug version or collect data files\n");
    printf
	("\tf) If box & line characters are letters then check: terminal emulator & $TERM\n");
    printf
	("\tg) External Data Collectors - nmon will execute a command or script at each snapshot time\n");
    printf
	("\t   They must output to a different file which is merge afterwards with the nmon output\n");
    printf("\t   Set the following shell variables:\n");
    printf
	("\t    NMON_START  = script to generate CVS Header test line explaining the columns\n");
    printf
	("\t         Generate: TabName,DataDescription,Column_name_and_units,Column_name_and_units ... \n");
    printf
	("\t    NMON_SNAP   = script for each snapshots data, the parameter is the T0000 snapshot number\n");
    printf("\t         Generate: TabName,T00NN,Data,Data,Data ...\n");
    printf
	("\t    NMON_END    = script to clean up or finalise the data\n");
    printf
	("\t    NMON_ONE_IN = call NMON_START less often (if it is heavy in CPU terms)\n");
    printf
	("\t    Once capture done: cat nmon-file data-file >merged-file ; ready for Analyser or other tools\n");
    printf
	("\t    The nmon Analyser will automatically do its best to graph the data on a new Tab sheet\n");
    printf("\n");
    printf
	("\tDeveloper: Nigel Griffiths      See http://nmon.sourceforge.net\n");
    printf("\tFeedback welcome - On the current release only\n");
    printf("\tNo warranty given or implied. (C) Copyright 2009 Nigel Griffiths GPLv3\n");
    exit(0);
}

#define JFSMAX 128
#define LOAD 1
#define UNLOAD 0
#define JFSNAMELEN 64
#define JFSTYPELEN 8

struct jfs {
    char name[JFSNAMELEN+1];
    char device[JFSNAMELEN+1];
    char type[JFSNAMELEN+1];
    int fd;
    int mounted;
} jfs[JFSMAX];

int jfses = 0;
void jfs_load(int load)
{
    int i;
    struct stat stat_buffer;
    FILE *mfp;			/* FILE pointer for mtab file */
    struct mntent *mp;		/* mnt point stats */
    static int jfs_loaded = 0;

    if (load == LOAD) {
	if (jfs_loaded == 0) {
	    mfp = setmntent("/etc/mtab", "r");
	    for (i = 0; i < JFSMAX && (mp = getmntent(mfp)) != NULL; i++) {
		strncpy(jfs[i].device, mp->mnt_fsname, JFSNAMELEN + 1);
		strncpy(jfs[i].name, mp->mnt_dir, JFSNAMELEN + 1);
		strncpy(jfs[i].type, mp->mnt_type, JFSTYPELEN + 1);
		mp->mnt_fsname[JFSNAMELEN] = 0;
		mp->mnt_dir[JFSNAMELEN] = 0;
		mp->mnt_type[JFSTYPELEN] = 0;
	    }
	    endmntent(mfp);
	    jfs_loaded = 1;
	    jfses = i;
	}

	/* 1st or later time - just reopen the mount points */
	for (jfses = 0, i = 0; i < JFSMAX && jfs[i].name[0] != 0; i++) {
	    if (stat(jfs[i].name, &stat_buffer) != -1) {
		jfs[i].fd = open(jfs[i].name, O_RDONLY);
		if (jfs[i].fd != -1) {
		    jfs[i].mounted = 1;
		} else {
		    jfs[i].mounted = 0;
		}
	    } else
		jfs[i].mounted = 0;
	}
	for (jfses = 0, i = 0; i < JFSMAX && jfs[i].name[0] != 0; i++) {
	    if (jfs[i].mounted == 1)
		jfses++;
	}
    } else {			/* this is an unload request */
	if (jfs_loaded) {
	    for (i = 0; i < JFSMAX && jfs[i].name[0] != 0; i++) {
		if (jfs[i].fd != 0)
		    close(jfs[i].fd);
		jfs[i].fd = 0;
	    }
	} 
    }
}

/* We order this array rather than the actual process tables
 * the index is the position in the process table and
 * the size is the memory used  in bytes
 * the io is the storge I/O performed in the the last period in bytes 
 * the time is the CPU used in the last period in seconds
 */
struct topper {
    int index;
    int other;
    double size;
    double io;
    int time;
} *topper;
int topper_size = 200;

/* Routine used by qsort to order the processes by CPU usage */
int cpu_compare(const void *a, const void *b)
{
    return (int) (((struct topper *) b)->time -
		  ((struct topper *) a)->time);
}

int size_compare(const void *a, const void *b)
{
    return (int) ((((struct topper *) b)->size -
		   ((struct topper *) a)->size));
}

int disk_compare(const void *a, const void *b)
{
    return (int) ((((struct topper *) b)->io - ((struct topper *) a)->io));
}


/* checkinput is the subroutine to handle user input */
int checkinput(void)
{
    static int use_env = 1;
    char buf[1024];
    int bytes;
    int chars;
    int i;
    char *p;

    if (!cursed)		/* not user input so stop with control-C */
	return 0;
    ioctl(fileno(stdin), FIONREAD, &bytes);

    if (bytes > 0 || use_env) {
	if (use_env) {
	    use_env = 0;
	    p = getenv("NMON");
	    if (p != 0) {
		strncpy(buf, p, 1024);
		buf[1024 - 1] = 0;
		chars = strlen(buf);
	    } else
		chars = 0;
	} else {
	    if(bytes > 1024) { /* block over flowing the buffer */
		bytes = 1023;
		buf[1023]=0;
	    }
	    chars = read(fileno(stdin), buf, bytes);
	}
	if (chars > 0) {
	    welcome = 0;
	    for (i = 0; i < chars; i++) {
		switch (buf[i]) {
		case '1':
		    show_topmode = 1;
		    show_top = 1;
		    wclear(padtop);
		    break;
/*					case '2':
					show_topmode = 2;
					show_top = 1;
					clear();
					break;
*/
		case '3':
		    show_topmode = 3;
		    show_top = 1;
		    wclear(padtop);
		    break;
		case '4':
		    show_topmode = 4;
		    show_top = 1;
		    wclear(padtop);
		    break;
		case '5':
		    if (isroot) {
			show_topmode = 5;
			show_top = 1;
			wclear(padtop);
		    }
		    break;
		case '0':
		    for (i = 0; i < (max_cpus + 1); i++)
			cpu_peak[i] = 0;
		    for (i = 0; i < networks; i++) {
			net_read_peak[i] = 0.0;
			net_write_peak[i] = 0.0;
		    }
		    for (i = 0; i < disks; i++) {
			disk_busy_peak[i] = 0.0;
			disk_rate_peak[i] = 0.0;
		    }
		    snap_clear();
		    aiocount_max = 0;
		    aiotime_max = 0.0;
		    aiorunning_max = 0;
		    huge_peak = 0;
		    break;
		case '6':
		case '7':
		case '8':
		case '9':
		    dotline = buf[i] - '0';
		    break;
		case ' ':	/* attempt to refresh the screen */
		    clear();
		    break;
		case '+':
		    seconds = seconds * 2;
		    break;
		case '-':
		    seconds = seconds / 2;
		    if (seconds < 1)
			seconds = 1;
		    break;
		case '.':	/* limit output to processes and disks actually doing work */
		    if (show_all)
			show_all = 0;
		    else {
			show_all = 1;
/* Switching to Nigel's favourite view is confusing to others
	so disable this feature.
			show_disk = SHOW_DISK_STATS;
			show_top = 1;
			show_topmode = 3;
*/
		    }
		    wclear(paddisk);
		    break;
		case '?':
		case 'h':
		case 'H':
		    if (show_help)
			show_help = 0;
		    else {
			show_help = 1;
			show_verbose = 0;
		    }
		    wclear(padhelp);
		    break;
/* alphabetic order from here */
#ifdef NVIDIA_GPU
		case 'a':	/* Accelerator */
		case 'E':	/* Emily mode */
		    FLIP(show_gpu);
		    wclear(padgpu);
		    break;
#endif				/* NVIDIA_GPU */
		case 'b':
		    FLIP(colour);
		    clear();
		    break;
		case 'c':
		    FLIP(show_smp);
		    wclear(padsmp);
		    break;
		case 'C':
		    FLIP(show_wide);
		    wclear(padwide);
		    break;
		case 'D':
		    switch (show_disk) {
		    case SHOW_DISK_NONE:
			show_disk = SHOW_DISK_STATS;
			break;
		    case SHOW_DISK_STATS:
			show_disk = SHOW_DISK_NONE;
			break;
		    case SHOW_DISK_GRAPH:
			show_disk = SHOW_DISK_STATS;
			break;
		    }
		    wclear(paddisk);
		    break;
		case 'd':
		    switch (show_disk) {
		    case SHOW_DISK_NONE:
			show_disk = SHOW_DISK_GRAPH;
			break;
		    case SHOW_DISK_STATS:
			show_disk = SHOW_DISK_GRAPH;
			break;
		    case SHOW_DISK_GRAPH:
			show_disk = 0;
			break;
		    }
		    wclear(paddisk);
		    break;

		    break;
		case 'G':
		    if (auto_dgroup) {
			FLIP(disk_only_mode);
			clear();
		    }
		    break;
		case 'g':
		    FLIP(show_dgroup);
		    wclear(paddg);
		    break;

		case 'j':
		    FLIP(show_jfs);
		    jfs_load(show_jfs);
		    wclear(padjfs);
		    break;
		case 'J':
		    FLIP(show_jfs_minimum);
		    wclear(padjfs);
		    break;
		case 'k':
		    FLIP(show_kernel);
		    wclear(padker);
		    break;
		case 'l':
		    FLIP(show_longterm);
		    wclear(padlong);
		    break;
		case 'L':
		    FLIP(show_large);
		    wclear(padlarge);
		    break;
		case 'm':
		    FLIP(show_memory);
		    wclear(padmem);
		    break;
		case 'M':
		    show_mhz++;
		    if (show_mhz == 4)
			show_mhz = 0;
		    wclear(padmhz);
		    break;
		case 'n':
		    if (show_net) {
			show_net = 0;
			show_neterror = 0;
		    } else {
			show_net = 1;
			show_neterror = 3;
		    }
		    wclear(padnet);
		    break;
		case 'N':
		    if (show_nfs == 0)
			show_nfs = 1;
		    else if (show_nfs == 1)
			show_nfs = 2;
		    else if (show_nfs == 2)
			show_nfs = 3;
		    else if (show_nfs == 3)
			show_nfs = 0;
		    nfs_clear = 1;
		    wclear(padnfs);
		    break;
		case 'o':
		    FLIP(show_diskmap);
		    wclear(padmap);
		    break;
#ifdef POWER
		case 'p':
		    FLIP(show_lpar);
		    wclear(padlpar);
		    break;
#endif
		case 'r':
		    FLIP(show_res);
		    wclear(padres);
		    break;
		case 't':
		    show_topmode = 3;	/* Fall Through */
		case 'T':
		    FLIP(show_top);
		    wclear(padtop);
		    break;
		case 'v':
		    FLIP(show_verbose);
		    wclear(padverb);
		    break;
		case 'u':
		    if (show_args == ARGS_NONE) {
			args_load();
			show_args = ARGS_ONLY;
			show_top = 1;
			if (show_topmode != 3 &&
			    show_topmode != 4 && show_topmode != 5)
			    show_topmode = 3;
		    } else
			show_args = ARGS_NONE;
		    wclear(padtop);
		    break;
		case 'U':
		    FLIP(show_util);
		    wclear(padutil);
		    break;
		case 'V':
		    FLIP(show_vm);
		    wclear(padpage);
		    break;
		case 'x':
		case 'q':
		    nocbreak();
		    endwin();
		    exit(0);
		default:
		    return 0;
		}
	    }
	    return 1;
	}
    }
    return 0;
}

void go_background(int def_loops, int def_secs)
{
    cursed = 0;
    if (maxloops == -1)
	maxloops = def_loops;
    if (seconds == -1)
	seconds = def_secs;
    show_res = 1;
    show_smp = 1;
    show_disk = SHOW_DISK_STATS;
    show_jfs = 1;
    show_memory = 1;
    show_large = 1;
    show_kernel = 1;
    show_net = 1;
    show_all = 1;
    show_top = 0;		/* top process */
    show_topmode = 3;
    show_lpar = 1;
    show_vm = 1;
}

void proc_net()
{
    static FILE *fp = (FILE *) - 1;
    char buf[1024];
    int i = 0;
    int ret;
    unsigned long junk;

    if (fp == (FILE *) - 1) {
	if ((fp = fopen("/proc/net/dev", "r")) == NULL) {
	    error("failed to open - /proc/net/dev");
	    networks = 0;
	    return;
	}
    }
    if (fgets(buf, 1024, fp) == NULL)
	goto end;		/* throw away the header lines */
    if (fgets(buf, 1024, fp) == NULL)
	goto end;		/* throw away the header lines */
/*
Inter-|   Receive                                                |  Transmit
 face |bytes    packets errs drop fifo frame compressed multicast|bytes    packets errs drop fifo colls carrier compressed
    lo:    1956      30    0    0    0     0          0         0     1956      30    0    0    0     0       0          0
  eth0:       0       0    0    0    0     0          0         0   458718       0  781    0    0     0     781          0
  sit0:       0       0    0    0    0     0          0         0        0       0    0    0    0     0       0          0
  eth1:       0       0    0    0    0     0          0         0        0       0    0    0    0     0       0          0
*/
    for (i = 0; i < NETMAX; i++) {
	if (fgets(buf, 1024, fp) == NULL)
	    break;
	strip_spaces(buf);
	/* 1   2   3    4   5   6   7   8   9   10   11   12  13  14  15  16 */
	ret =
	    sscanf(&buf[0],
		   "%s %llu %llu %lu %lu %lu %lu %lu %lu %llu %llu %lu %lu %lu %lu %lu",
		   (char *) &p->ifnets[i].if_name, &p->ifnets[i].if_ibytes,
		   &p->ifnets[i].if_ipackets, &p->ifnets[i].if_ierrs,
		   &p->ifnets[i].if_idrop, &p->ifnets[i].if_ififo,
		   &p->ifnets[i].if_iframe, &junk, &junk,
		   &p->ifnets[i].if_obytes, &p->ifnets[i].if_opackets,
		   &p->ifnets[i].if_oerrs, &p->ifnets[i].if_odrop,
		   &p->ifnets[i].if_ofifo, &p->ifnets[i].if_ocolls,
		   &p->ifnets[i].if_ocarrier);
	if (ret != 16)
	    fprintf(stderr, "sscanf wanted 16 returned = %d line=%s\n",
		    ret, (char *) buf);
    }
  end:
    if (reread) {
	fclose(fp);
	fp = (FILE *) - 1;
    } else
	rewind(fp);
    networks = i;
}


int proc_procsinfo(int pid, int index)
{
    FILE *fp;
    char filename[64];
    char buf[1024 * 4];
    int size = 0;
    int ret = 0;
    int count = 0;
    int i;

    snprintf(filename, 64, "/proc/%d/stat", pid);
    if ((fp = fopen(filename, "r")) == NULL) {
	snprintf(buf, 1024 * 4, "failed to open file %s", filename);
	error(buf);
	return 0;
    }
    size = fread(buf, 1, 1024 - 1, fp);
    fclose(fp);
    if (size == -1) {
#ifdef DEBUG
	fprintf(stderr,
		"procsinfo read returned = %d assuming process stopped pid=%d\n",
		ret, pid);
#endif	 /*DEBUG*/
	    return 0;
    }
    ret = sscanf(buf, "%d (%s)",
		 &p->procs[index].pi_pid, &p->procs[index].pi_comm[0]);
    if (ret != 2) {
	fprintf(stderr, "procsinfo sscanf returned = %d line=%s\n", ret,
		buf);
	return 0;
    }
    p->procs[index].pi_comm[strlen(p->procs[index].pi_comm) - 1] = 0;

    for (count = 0; count < size; count++)	/* now look for ") " as dumb Infiniban driver includes "()" */
	if (buf[count] == ')' && buf[count + 1] == ' ')
	    break;

    if (count == size) {
#ifdef DEBUG
	fprintf(stderr, "procsinfo failed to find end of command buf=%s\n",
		buf);
#endif	 /*DEBUG*/
	    return 0;
    }
    count++;
    count++;

    ret = sscanf(&buf[count],
#ifdef PRE_KERNEL_2_6_18
		 "%c %d %d %d %d %d %lu %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %lu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d",
#else
		 "%c %d %d %d %d %d %lu %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %lu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %lu %lu %llu",
#endif
		 &p->procs[index].pi_state,
		 &p->procs[index].pi_ppid,
		 &p->procs[index].pi_pgrp,
		 &p->procs[index].pi_session,
		 &p->procs[index].pi_tty_nr,
		 &p->procs[index].pi_tty_pgrp,
		 &p->procs[index].pi_flags,
		 &p->procs[index].pi_minflt,
		 &p->procs[index].pi_cmin_flt,
		 &p->procs[index].pi_majflt,
		 &p->procs[index].pi_cmaj_flt,
		 &p->procs[index].pi_utime,
		 &p->procs[index].pi_stime,
		 &p->procs[index].pi_cutime,
		 &p->procs[index].pi_cstime,
		 &p->procs[index].pi_pri, &p->procs[index].pi_nice,
#ifdef PRE_KERNEL_2_6_18
		 &p->procs[index].junk,
#else
		 &p->procs[index].pi_num_threads,
#endif
		 &p->procs[index].pi_it_real_value,
		 &p->procs[index].pi_start_time,
		 &p->procs[index].pi_vsize,
		 &p->procs[index].pi_rss,
		 &p->procs[index].pi_rlim_cur,
		 &p->procs[index].pi_start_code,
		 &p->procs[index].pi_end_code,
		 &p->procs[index].pi_start_stack,
		 &p->procs[index].pi_esp,
		 &p->procs[index].pi_eip,
		 &p->procs[index].pi_pending_signal,
		 &p->procs[index].pi_blocked_sig,
		 &p->procs[index].pi_sigign,
		 &p->procs[index].pi_sigcatch,
		 &p->procs[index].pi_wchan,
		 &p->procs[index].pi_nswap,
		 &p->procs[index].pi_cnswap,
		 &p->procs[index].pi_exit_signal, &p->procs[index].pi_cpu
#ifndef PRE_KERNEL_2_6_18
		 ,
		 &p->procs[index].pi_rt_priority,
		 &p->procs[index].pi_policy,
		 &p->procs[index].pi_delayacct_blkio_ticks
#endif
	);
#ifdef PRE_KERNEL_2_6_18
    if (ret != 37) {
	fprintf(stderr,
		"procsinfo2 sscanf wanted 37 returned = %d pid=%d line=%s\n",
		ret, pid, buf);
#else
    if (ret != 40) {
	fprintf(stderr,
		"procsinfo2 sscanf wanted 40 returned = %d pid=%d line=%s\n",
		ret, pid, buf);
#endif
	return 0;
    }

    snprintf(filename, 64, "/proc/%d/statm", pid);
    if ((fp = fopen(filename, "r")) == NULL) {
	snprintf(buf, 1024 * 4, "failed to open file %s", filename);
	error(buf);
	return 0;
    }
    size = fread(buf, 1, 1024 * 4 - 1, fp);
    fclose(fp);			/* close it even if the read failed, the file could have been removed 
				   between open & read i.e. the device driver does not behave like a file */
    if (size == -1) {
	snprintf(buf, 1024 * 4, "failed to read file %s", filename);
	error(buf);
	return 0;
    }

    ret = sscanf(&buf[0], "%lu %lu %lu %lu %lu %lu %lu",
		 &p->procs[index].statm_size,
		 &p->procs[index].statm_resident,
		 &p->procs[index].statm_share,
		 &p->procs[index].statm_trs,
		 &p->procs[index].statm_lrs,
		 &p->procs[index].statm_drs, &p->procs[index].statm_dt);
    if (ret != 7) {
	fprintf(stderr, "sscanf wanted 7 returned = %d line=%s\n", ret,
		buf);
	return 0;
    }
    if (isroot) {
	p->procs[index].read_io = 0;
	p->procs[index].write_io = 0;
	snprintf(filename, 64, "/proc/%d/io", pid);
	if ((fp = fopen(filename, "r")) != NULL) {
	    for (i = 0; i < 6; i++) {
		if (fgets(buf, 1024, fp) == NULL) {
		    break;
		}
		if (strncmp("read_bytes:", buf, 11) == 0)
		    sscanf(&buf[12], "%lld", &p->procs[index].read_io);
		if (strncmp("write_bytes:", buf, 12) == 0)
		    sscanf(&buf[13], "%lld", &p->procs[index].write_io);
	    }
	}

	if (fp != NULL)
	    fclose(fp);
    }
    return 1;
}

#ifdef DEBUGPROC
print_procs(int index)
{
    printf("procs[%d].pid           =%d\n", index, procs[index].pi_pid);
    printf("procs[%d].comm[0]       =%s\n", index,
	   &procs[index].pi_comm[0]);
    printf("procs[%d].state         =%c\n", index, procs[index].pi_state);
    printf("procs[%d].ppid          =%d\n", index, procs[index].pi_ppid);
    printf("procs[%d].pgrp          =%d\n", index, procs[index].pi_pgrp);
    printf("procs[%d].session       =%d\n", index,
	   procs[index].pi_session);
    printf("procs[%d].tty_nr        =%d\n", index, procs[index].pi_tty_nr);
    printf("procs[%d].tty_pgrp      =%d\n", index,
	   procs[index].pi_tty_pgrp);
    printf("procs[%d].flags         =%lu\n", index, procs[index].pi_flags);
    printf("procs[%d].minflt       =%lu\n", index, procs[index].pi_minflt);
    printf("procs[%d].cmin_flt     =%lu\n", index,
	   procs[index].pi_cmin_flt);
    printf("procs[%d].majflt       =%lu\n", index, procs[index].pi_majflt);
    printf("procs[%d].cmaj_flt     =%lu\n", index,
	   procs[index].pi_cmaj_flt);
    printf("procs[%d].utime        =%lu\n", index, procs[index].pi_utime);
    printf("procs[%d].stime        =%lu\n", index, procs[index].pi_stime);
    printf("procs[%d].cutime       =%ld\n", index, procs[index].pi_cutime);
    printf("procs[%d].cstime       =%ld\n", index, procs[index].pi_cstime);
    printf("procs[%d].pri           =%d\n", index, procs[index].pi_pri);
    printf("procs[%d].nice          =%d\n", index, procs[index].pi_nice);
#ifdef PRE_KERNEL_2_6_18
    printf("procs[%d].junk          =%d\n", index, procs[index].junk);
#else
    printf("procs[%d].num_threads   =%ld\n", index,
	   procs[index].num_threads);
#endif
    printf("procs[%d].it_real_value =%lu\n", index,
	   procs[index].pi_it_real_value);
    printf("procs[%d].start_time    =%lu\n", index,
	   procs[index].pi_start_time);
    printf("procs[%d].vsize         =%lu\n", index, procs[index].pi_vsize);
    printf("procs[%d].rss           =%lu\n", index, procs[index].pi_rss);
    printf("procs[%d].rlim_cur      =%lu\n", index,
	   procs[index].pi_rlim_cur);
    printf("procs[%d].start_code    =%lu\n", index,
	   procs[index].pi_start_code);
    printf("procs[%d].end_code      =%lu\n", index,
	   procs[index].pi_end_code);
    printf("procs[%d].start_stack   =%lu\n", index,
	   procs[index].pi_start_stack);
    printf("procs[%d].esp           =%lu\n", index, procs[index].pi_esp);
    printf("procs[%d].eip           =%lu\n", index, procs[index].pi_eip);
    printf("procs[%d].pending_signal=%lu\n", index,
	   procs[index].pi_pending_signal);
    printf("procs[%d].blocked_sig   =%lu\n", index,
	   procs[index].pi_blocked_sig);
    printf("procs[%d].sigign        =%lu\n", index,
	   procs[index].pi_sigign);
    printf("procs[%d].sigcatch      =%lu\n", index,
	   procs[index].pi_sigcatch);
    printf("procs[%d].wchan         =%lu\n", index, procs[index].pi_wchan);
    printf("procs[%d].nswap         =%lu\n", index, procs[index].pi_nswap);
    printf("procs[%d].cnswap        =%lu\n", index,
	   procs[index].pi_cnswap);
    printf("procs[%d].exit_signal   =%d\n", index,
	   procs[index].pi_exit_signal);
    printf("procs[%d].cpu           =%d\n", index, procs[index].pi_cpu);
#ifndef PRE_KERNEL_2_6_18
    printf("procs[%d].rt_priority   =%lu\n", index,
	   procs[index].pi_rt_priority);
    printf("procs[%d].policy        =%lu\n", index,
	   procs[index].pi_policy);
    printf("procs[%d].delayacct_blkio_ticks=%llu\n", index,
	   procs[index].pi_delayacct_blkio_ticks);
#endif
    printf("OK\n");
}
#endif /*DEBUG*/
/* --- */
int isnumbers(char *s)
{
    while (*s != 0) {
	if (*s < '0' || *s > '9')
	    return 0;
	s++;
    }
    return 1;
}

int getprocs(int records)
{
    struct dirent *dent;
    DIR *procdir;
    int count = 0;

    if ((char *) (procdir = opendir("/proc")) == NULL) {
	printf("opendir(/proc) failed");
	return 0;
    }
    while ((char *) (dent = readdir(procdir)) != NULL) {
	if (dent->d_type == 4) {	/* is this a directlory */
	/* mainframes report 0 = unknown every time !!!!  */
	    if (isnumbers(dent->d_name)) {
		if (records != 0) {
		    /* getting the details mode */
		    count = count + proc_procsinfo(atoi(dent->d_name), count);
		    if(count == records) {
			break;
		    }
		} else {
		    /* just counting the processes mode */
		    count++;
		}
	    }
	}
    }
    closedir(procdir);
    return count;
}

/* --- */

char cpu_line[] =
    "---------------------------+-------------------------------------------------+";
/* Start process as specified in cmd in a child process without waiting
 * for completion
 * not sure if want to prevent this funcitonality for root user
 * when: CHLD_START, CHLD_SNAP or CHLD_END
 * cmd:  pointer to command string - assumed to be cleansed ....
 * timestamp_type: 0 - T%04d, 1 - detailed time stamp
 * loop: loop id (0 for CHLD_START)
 * the_time: time to use for timestamp generation
 */
void child_start(int when,
		 char *cmd, int timestamp_type, int loop, time_t the_time)
{
    int i;
    pid_t child_pid;
    char time_stamp_str[64] = "";
    char *when_info = "";
    struct tm *tim;		/* used to work out the hour/min/second */

#ifdef DEBUG2
    fprintf(fp, "child start when=%d cmd=%s time=%d loop=%d\n", when, cmd,
	    timestamp_type, loop);
#endif
    /* Validate parameter and initialize error text */
    switch (when) {
    case CHLD_START:
	when_info = "nmon fork exec failure CHLD_START";
	break;
    case CHLD_END:
	when_info = "nmon fork exec failure CHLD_END";
	break;

    case CHLD_SNAP:
	/* check if old child has finished - otherwise we do nothing */
	if (nmon_children[CHLD_SNAP] != -1) {
	    if (!cursed)
		fprintf(fp,
			"ERROR,T%04d, Starting snap command \"%s\" failed as previous child still running - killing it now\n",
			loop, cmd);
	    kill(nmon_children[CHLD_SNAP], 9);
	}

	when_info = "nmon fork exec failure CHLD_SNAP";
	break;
    }


    /* now fork off a child process. */
    switch (child_pid = fork()) {
    case -1:			/* fork failed. */
	perror(when_info);
	return;

    case 0:			/* inside child process.  */
	/* create requested timestamp */
	if (timestamp_type == 1) {
	    tim = localtime(&the_time);
	    snprintf(time_stamp_str, 64, "%02d:%02d:%02d,%02d,%02d,%04d",
		    tim->tm_hour, tim->tm_min, tim->tm_sec,
		    tim->tm_mday, tim->tm_mon + 1, tim->tm_year + 1900);
	} else {
	    snprintf(time_stamp_str, 64, "T%04d", loop);
	}

	/* close all open file pointers except the defaults */
	for (i = 3; i < 5; ++i)
	    close(i);

	/* Now switch to the defined command */
	execlp(cmd, cmd, time_stamp_str, (void *) 0);

	/* If we get here the specified command could not be started */
	perror(when_info);
	exit(1);		/* We can't do anything more */
	/* never reached */

    default:			/* inside parent process. */
	/* In father - remember child pid for future */
	nmon_children[when] = child_pid;
    }
}

int main(int argc, char **argv)
{
    int secs;
    int cpu_idle;
    int cpu_user;
    int cpu_sys;
    int cpu_wait;
    int cpu_steal;
    int current_procs = 0;
    int adjusted_procs = 0;
    int n = 0;			/* reusable counters */
    int i = 0;
    int j = 0;
    int k = 0;
    int ret = 0;
    int max_sorted;
    int skipped;
    int x = 0;			/* curses row */
    int y = 0;			/* curses column */
    double elapsed;		/* actual seconds between screen updates */
    double cpu_sum;
    double ftmp;
    int top_first_time = 1;
    int disk_first_time = 1;
    int nfs_first_time = 1;
    int vm_first_time = 1;
    int bbbr_line = 0;
    double cpu_busy;
#ifdef POWER
    int lpar_first_time = 1;
    long max_speed = 0;
#endif				/* POWER */
    int smp_first_time = 1;
    int wide_first_time = 1;
    int proc_first_time = 1;
    int first_key_pressed = 0;
    pid_t childpid = -1;
    int ralfmode = 0;
    char pgrp[32];
    struct tm *tim;		/* used to work out the hour/min/second */
    float total_busy;		/* general totals */
    float total_rbytes;		/* general totals */
    float total_wbytes;
    float total_xfers;
    struct utsname uts;		/* UNIX name, version, etc */
    double top_disk_busy = 0.0;
    char *top_disk_name = "";
    int disk_mb;
    double disk_total;
    double disk_busy;
    double disk_read;
    double disk_read_tmp;
    double disk_write;
    double disk_write_tmp;
    double disk_size;
    double disk_xfers;
    double total_disk_read;
    double total_disk_write;
    double total_disk_xfers;
    double readers;
    double writers;

    /* for popen on oslevel */
    char *str_p;
    int varperftmp = 0;
    char *formatstring;
    char *open_filename = 0;
    char *user_filename = 0;
    char user_filename_set = 0;
    char using_stdout = 0;
    struct statfs statfs_buffer;

    float fs_size;
    float fs_bsize;
    float fs_free;
    float fs_size_used;

    char cmdstr[256];
    long updays, uphours, upmins;
    float v2c_total;
    float v2s_total;
    float v3c_total;
    float v3s_total;
    float v4c_total;
    float v4s_total;
    int errors = 0;

    char *nmon_start = (char *) NULL;
    char *nmon_end = (char *) NULL;
    char *nmon_snap = (char *) NULL;
    char *nmon_tmp = (char *) NULL;
    int nmon_one_in = 1;
    /* Flag what kind of time stamp we give to started children
     * 0: "T%04d"
     * 1: "hh:mm:ss,dd,mm,yyyy"
     */
    int time_stamp_type = 0;
    long ticks = 100;		/* Clock ticks per second used in /proc/stat cpu lines */
    unsigned long pagesize = 1024 * 4;	/* Default page size is 4 KB but newer servers compiled with 64 KB pages */
    float average;
    struct timeval nmon_tv;	/* below is used to workout the nmon run, accumalate it and the 
				   allow for in in the sleep time  to reduce time drift */
    double nmon_start_time = 0.0;
    double nmon_end_time = 0.0;
    double nmon_run_time = -1.0;
    int seconds_over = 0;
    float mhz;
    float min_mhz;
    float max_mhz;
    float avg_mhz = 0.0;
    unsigned long topsize;
    char topsize_ch;
    unsigned long toprset;
    char toprset_ch;
    unsigned long toptrs;
    char toptrs_ch;
    unsigned long topdrs;
    char topdrs_ch;
    unsigned long toplrs;
    char toplrs_ch;
    unsigned long topshare;
    char topshare_ch;
    unsigned long toprio;
    char toprio_ch;
    unsigned long topwio;
    char topwio_ch;
    long long tmpslab;
    char * slabstr;
    char truncated_command[257]; /* 256 +1 */


#define MAXROWS 256
#define MAXCOLS 150		/* changed to allow maximum column widths */
#define BANNER(pad,string) {mvwhline(pad, 0, 0, ACS_HLINE,COLS-2); \
                                        wmove(pad,0,0); \
                                        wattron(pad,A_STANDOUT); \
                                        wprintw(pad," "); \
                                        wprintw(pad,string); \
                                        wprintw(pad," "); \
                                        wattroff(pad,A_STANDOUT); }

#define DISPLAY(pad,rows) { \
                        if(x+2+(rows)>LINES)\
                                pnoutrefresh(pad, 0,0,x,1,LINES-2, COLS-2); \
                        else \
                                pnoutrefresh(pad, 0,0,x,1,x+rows+1,COLS-2); \
                        x=x+(rows);     \
                        if(x+4>LINES) { \
                                mvwprintw(stdscr,LINES-1,10,"Warning: Some Statistics may not shown"); \
                        }               \
                       }

    /* check the user supplied options */
    progname = argv[0];
    for (i = (int) strlen(progname) - 1; i > 0; i--)
	if (progname[i] == '/') {
	    progname = &progname[i + 1];
	}

    if (getenv("NMONDEBUG") != NULL)
	debug = 1;
    if (getenv("NMONERROR") != NULL)
	error_on = 1;
    if (getenv("NMONBUG1") != NULL)
	reread = 1;

/* External Data Collector Controls */
    if ((nmon_start = getenv("NMON_START")) != NULL) {
	nmon_start = check_call_string(nmon_start, "NMON_START");
    }
    if ((nmon_end = getenv("NMON_END")) != NULL) {
	nmon_end = check_call_string(nmon_end, "NMON_END");
    }
    if ((nmon_tmp = getenv("NMON_ONE_IN")) != NULL) {
	nmon_one_in = atoi(nmon_tmp);
	if (errno != 0) {
	    fprintf(stderr,
		    "ERROR nmon: invalid NMON_ONE_IN shell variable\n");
	    nmon_one_in = 1;
	}
    }
    if ((nmon_snap = getenv("NMON_SNAP")) != NULL) {
	nmon_snap = check_call_string(nmon_snap, "NMON_SNAP");
    }
    if ((nmon_tmp = getenv("NMON_TIMESTAMP")) != NULL) {
	time_stamp_type = atoi(nmon_tmp);
	if (time_stamp_type != 0 && time_stamp_type != 1)
	    time_stamp_type = 1;
    }
#ifdef DEBUG2
    printf("NMON_START=%s.\n", nmon_start);
    printf("NMON_END=%s.\n", nmon_end);
    printf("NMON_SNAP=%s.\n", nmon_snap);
    printf("ONE_IN=%d.\n", nmon_one_in);
    printf("TIMESTAMP=%d.\n", time_stamp_type);
#endif

#ifdef REREAD
    reread = 1;
#endif
    for (i = 0; i < CMDMAX; i++) {
	snprintf(cmdstr, 256, "NMONCMD%d", i);
	cmdlist[i] = getenv(cmdstr);
	if (cmdlist[i] != 0)
	    cmdfound = i + 1;
    }
    /* Setup long and short Hostname */
    gethostname(hostname, sizeof(hostname));
    strncpy(fullhostname, hostname, 256);
    fullhostname[256 - 1] = 0;
    for (i = 0; i < sizeof(hostname); i++)
	if (hostname[i] == '.')
	    hostname[i] = 0;
    if (run_name_set == 0) {
	strncpy(run_name, hostname, 256);
	run_name[256 - 1] = 0;
    }
    if (getuid() == 0)
	isroot = 1;

    /* Check the version of OS */
    uname(&uts);
    /* Get the clock ticks persecond for CPU counters in /proc/stat cpu stats */
    ticks = sysconf(_SC_CLK_TCK);
    if (ticks == -1 || ticks == 0)
	ticks = 100;
    /* Check if we have the large 64 KB memory page sizes compiled into the kernel */
    if (sysconf(_SC_PAGESIZE) > 1024 * 4)
	pagesize = sysconf(_SC_PAGESIZE);
    proc_init();

    while (-1 !=
	   (i =
	    getopt(argc, argv,
		   "?abc:C:Dd:EfF:g:hI:Jl:m:MNpr:Rs:tTUVxXz"))) {
	switch (i) {
	case '?':
	    hint();
	    exit(0);
	case 'a':		/* Acelerator */
	case 'E':		/* Emily */
	    show_gpu = 1;
	    break;
	case 'b':
	    colour = 0;
	    break;
	case 'c':
	    maxloops = atoi(optarg);
	    break;
	case 'C':		/* commandlist argument */
	    cmdlist[0] = MALLOC(strlen(optarg) + 1);	/* create buffer */
	    strcpy(cmdlist[0], optarg);
	    if (cmdlist[0][0] != 0)
		cmdfound = 1;
	    for (i = 0, j = 1; cmdlist[0][i] != 0; i++) {
		if (cmdlist[0][i] == ':') {
		    cmdlist[0][i] = 0;
		    cmdlist[j] = &cmdlist[0][i + 1];
		    j++;
		    cmdfound = j;
		    if (j >= CMDMAX)
			break;
		}
	    }
	    break;
	case 'd':
	    diskmax = atoi(optarg);
	    if (diskmax < DISKMIN) {
		printf
		    ("nmon: ignoring -d %d option as the minimum is %d\n",
		     diskmax, DISKMIN);
		diskmax = DISKMIN;
	    }
	    break;
	case 'D':
	    extended_disk = 1;
	    break;
	case 'F':		/* background mode with user supplied filename */
	    user_filename = MALLOC(strlen(optarg) + 1);
	    strcpy(user_filename, optarg);
	    user_filename_set++;
	    go_background(288, 300);
	    break;
	case 'f':		/* background mode i.e. for spread sheet output */
	    go_background(288, 300);
	    break;
	case 'g':		/* disk groups */
	    show_dgroup = 1;
	    dgroup_loaded = 1;
	    dgroup_filename = optarg;
	    if (strncmp("auto", dgroup_filename, 5) == 0) {
		auto_dgroup++;
		printf
		    ("Generating disk group file from lsblk output to file: \"auto\"\n");
#ifdef SLES113
#define LSBLK_NO_TYPE		/* define this to work around missing --output TYPE feature */
#endif				/* SLES113 */

#ifdef LSBLK_NO_TYPE
#define LSBLK_STRING "lsblk --nodeps --output NAME --noheadings | awk 'BEGIN {printf \"# This file created by: nmon -g auto\\n# It is an automatically generated disk-group file which excluses disk paritions\\n\" } { printf \"%s %s\\n\", $1, $1 }' >auto"
#else
#define LSBLK_STRING "lsblk --nodeps --output NAME,TYPE --raw | grep disk | awk 'BEGIN {printf \"# This file created by: nmon -g auto\\n# It is an automatically generated disk-group file which excluses disk paritions\\n\" } { printf \"%s %s\\n\", $1, $1 }' >auto"
#endif				/* LSBLK_NO_TYPE */
		ret = system(LSBLK_STRING);
		if (ret != 0) {
		    printf("Create auto file command was: %s\n", LSBLK_STRING);
		    printf("Creating auto file returned a status of %d\n", ret);
		}
	    }
	    break;
	case 'h':
	    help();
	    break;
	case 'I':
	    ignore_procdisk_threshold = atof(optarg);
	    break;
	case 'J':
	    show_jfs = 0;
	    break;
	case 'l':
	    disks_per_line = atoi(optarg);
	    if (disks_per_line < 3 || disks_per_line > 250)
		disks_per_line = 100;
	    break;
	case 'm':
	    if (chdir(optarg) == -1) {
		perror("changing directory failed");
		printf("Directory attempted was:%s\n", optarg);
		exit(993);
	    }
	    break;
	case 'M':		/* MHz */
	    show_mhz = 1;
	    break;
	case 'N':
	    show_nfs = 1;
	    break;
	case 'p':
	    ralfmode = 1;
	    break;
	case 'R':
	    show_rrd = 1;
	    go_background(288, 300);
	    show_aaa = 0;
	    show_para = 0;
	    show_headings = 0;
	    break;
	case 'r':
	    strncpy(run_name, optarg, 256);
	    run_name[256 - 1] = 0;
	    run_name_set++;
	    break;
	case 's':
	    seconds = atoi(optarg);
	    break;
	case 'T':
	    show_args = ARGS_ONLY;	/* drop through */
	case 't':
	    show_top = 1;	/* put top process output in spreadsheet mode */
	    show_topmode = 3;
	    break;
	case 'U':
	    show_util = 1;
	    break;
	case 'V':		/* nmon version */
	    printf("nmon version %s\n", VERSION);
	    exit(0);
	    break;
	case 'x':		/* background mode for 1 day capacity planning */
	    go_background(4 * 24, 15 * 60);
	    show_top = 1;
	    show_topmode = 3;
	    break;
	case 'X':		/* background mode for 1 hour capacity planning */
	    go_background(120, 30);
	    show_top = 1;
	    show_topmode = 3;
	    break;
	case 'z':		/* background mode for 1 day output to /var/perf/tmp */
	    varperftmp++;
	    go_background(4 * 24, 15 * 60);
	    break;
	}
    }
    /* Set parameters if not set by above */
    if (maxloops == -1)
	maxloops = 9999999;
    if (seconds == -1)
	seconds = 2;
    if (cursed)
	show_dgroup = 0;

    /* -D need -g filename */
    if (extended_disk == 1 && show_dgroup == 0) {
	printf
	    ("nmon: ignoring -D (extended disk stats) as -g filename is missing\n");
	extended_disk = 0;
    }
#ifdef NVIDIA_GPU
    if (cursed) {
	gpu_init();
    }
#endif				/* NVIDIA_GPU */

    /* To get the pointers setup */
    switcher();

    /* Initialise the time stamps for the first loop */
    p->time = doubletime();
    q->time = doubletime();

    find_release();

    /* Determine number of active LOGICAL cpu - depends on SMT mode ! */
    get_cpu_cnt();
    max_cpus = old_cpus = cpus;
#if X86 || ARM
    get_intel_spec();
#endif
    proc_read(P_STAT);
    proc_cpu();
    proc_read(P_UPTIME);
    proc_read(P_LOADAVG);
    proc_kernel();
    memcpy(&q->cpu_total, &p->cpu_total, sizeof(struct cpu_stat));

    p->dk = MALLOC(sizeof(struct dsk_stat) * diskmax + 1);
    q->dk = MALLOC(sizeof(struct dsk_stat) * diskmax + 1);
    disk_busy_peak = MALLOC(sizeof(double) * diskmax);
    disk_rate_peak = MALLOC(sizeof(double) * diskmax);
    for (i = 0; i < diskmax; i++) {
	disk_busy_peak[i] = 0.0;
	disk_rate_peak[i] = 0.0;
    }

    cpu_peak = MALLOC(sizeof(double) * (CPUMAX + 1));	/* MAGIC */
    for (i = 0; i < max_cpus + 1; i++)
	cpu_peak[i] = 0.0;

    current_procs = getprocs(0);
    adjusted_procs = current_procs + 128; /*allows for more processes */
    p->procs = MALLOC(sizeof(struct procsinfo) * adjusted_procs);
    q->procs = MALLOC(sizeof(struct procsinfo) * adjusted_procs);
    p->proc_records = adjusted_procs;
    q->proc_records = adjusted_procs;
    p->processes = 0;
    q->processes = 0;

    /* Initialise the top processes table */
    topper_size = n;
    topper = MALLOC(sizeof(struct topper) * topper_size);	/* round up */

    /* Get Disk Stats. */
    proc_disk(0.0);
    memcpy(q->dk, p->dk, sizeof(struct dsk_stat) * disks);

    /* load dgroup - if required */
    if (dgroup_loaded == 1) {
	load_dgroup(p->dk);
    }

    /* Get Network Stats. */
    proc_net();
    memcpy(q->ifnets, p->ifnets, sizeof(struct net_stat) * networks);
    for (i = 0; i < networks; i++) {
	net_read_peak[i] = 0.0;
	net_write_peak[i] = 0.0;
    }

    /* If we are running in spreadsheet mode initialize all other data sets as well
     * so we do not get incorrect data for the first reported interval
     */
    if (!cursed) {
	/* Get VM Stats */
	read_vmstat();

	/* Get Memory info */
	proc_mem();

#ifdef POWER
	/* Get LPAR Stats */
	proc_lparcfg();
#endif
    }
    /* Set the pointer ready for the next round */
    switcher();

    /* Initialise signal handlers so we can tidy up curses on exit */
    signal(SIGUSR1, interrupt);
    signal(SIGUSR2, interrupt);
    signal(SIGINT, interrupt);
    signal(SIGWINCH, interrupt);
    signal(SIGCHLD, interrupt);

    /* Start Curses */
    if (cursed) {
	initscr();
	cbreak();
	move(0, 0);
	refresh();
	COLOUR colour = has_colors();
	COLOUR start_color();
	COLOUR init_pairs();
	clear();
#ifdef POWER
	padlpar = newpad(11, MAXCOLS);
#endif
	padwelcome = newpad(24, MAXCOLS);
	padmap = newpad(24, MAXCOLS);
	padhelp = newpad(24, MAXCOLS);
	padmem = newpad(20, MAXCOLS);
	padlarge = newpad(20, MAXCOLS);
	padpage = newpad(20, MAXCOLS);
	padres = newpad(20, MAXCOLS);
	padsmp = newpad(MAXROWS, MAXCOLS);
	padutil = newpad(MAXROWS, MAXCOLS);
	padlong = newpad(MAXROWS, MAXCOLS);
	padwide = newpad(MAXROWS, MAXCOLS);
	padmhz = newpad(24, MAXCOLS);
	padgpu = newpad(10, MAXCOLS);
	padnet = newpad(MAXROWS, MAXCOLS);
	padneterr = newpad(MAXROWS, MAXCOLS);
	paddisk = newpad(MAXROWS, MAXCOLS);
	paddg = newpad(MAXROWS, MAXCOLS);
	padjfs = newpad(MAXROWS, MAXCOLS);
	padker = newpad(12, MAXCOLS);
	padverb = newpad(8, MAXCOLS);
	padnfs = newpad(25, MAXCOLS);
	padtop = newpad(MAXROWS, MAXCOLS * 2);


    } else {
	/* Output the header lines for the spread sheet */
	timer = time(0);
	tim = localtime(&timer);
	tim->tm_year += 1900 - 2000;	/* read localtime() manual page!! */
	tim->tm_mon += 1;	/* because it is 0 to 11 */
	if (varperftmp) {
	    if(strlen(hostname) > 1024 )
		    hostname[255] = 0;
	    open_filename = MALLOC(strlen(hostname) + 64); /* hostname plus directory size plus the number */
	    snprintf(open_filename, strlen(hostname) + 63,  "/var/perf/tmp/%s_%02d.nmon", hostname,
		    tim->tm_mday);
	}
	else if (user_filename_set && user_filename != 0) {
	    open_filename = MALLOC(strlen(user_filename) + 1);
	    strcpy(open_filename, user_filename);
	}
	else {
	    open_filename = MALLOC(strlen(hostname) + 64);
	    snprintf(open_filename, strlen(hostname) + 63, "%s_%02d%02d%02d_%02d%02d.nmon",
		    hostname,
		    tim->tm_year,
		    tim->tm_mon, tim->tm_mday, tim->tm_hour, tim->tm_min);
	}
	if (!strncmp(open_filename, "stdout", 6)) {
		using_stdout = 1;
		if ((fp = fdopen(1, "w")) == 0) {
		    perror("nmon: failed to open standard output");
		    exit(41);
		}
	} else {
		if ((fp = fopen(open_filename, "w")) == 0) {
		    perror("nmon: failed to open output file");
		    printf("nmon: output filename=%s\n", open_filename);
		    exit(42);
		}
	}
	free(open_filename);
	/* disconnect from terminal */
	fflush(NULL);
	if (!debug && (childpid = fork()) != 0) {
	    if (ralfmode)
		printf("%d\n", childpid);
	    exit(0);		/* parent returns OK */
	}
	if (!debug) {
	    close(0);
	    if(using_stdout == 0)
		close(1);
	    close(2);
	    setpgrp();		/* become process group leader */
	    signal(SIGHUP, SIG_IGN);	/* ignore hangups */
	}
	/* Do the nmon_start activity early on */
	if (nmon_start) {
	    timer = time(0);
	    child_start(CHLD_START, nmon_start, time_stamp_type, 1, timer);
	}

	if (show_aaa) {
	    fprintf(fp, "AAA,progname,%s\n", progname);
	    fprintf(fp, "AAA,command,");
	    for (i = 0; i < argc; i++)
		fprintf(fp, "%s ", argv[i]);
	    fprintf(fp, "\n");
	    fprintf(fp, "AAA,version,%s\n", VERSION);
	    fprintf(fp, "AAA,disks_per_line,%d\n", disks_per_line);
	    fprintf(fp, "AAA,max_disks,%d,set by -d option\n", diskmax);
	    fprintf(fp, "AAA,disks,%d,\n", disks);

	    fprintf(fp, "AAA,host,%s\n", hostname);
	    fprintf(fp, "AAA,user,%s\n", getenv("USER"));
	    fprintf(fp, "AAA,OS,Linux,%s,%s,%s\n", uts.release,
		    uts.version, uts.machine);
	    fprintf(fp, "AAA,runname,%s\n", run_name);
	    fprintf(fp, "AAA,time,%02d:%02d.%02d\n", tim->tm_hour,
		    tim->tm_min, tim->tm_sec);
	    fprintf(fp, "AAA,date,%02d-%3s-%02d\n", tim->tm_mday,
		    month[tim->tm_mon - 1], tim->tm_year + 2000);
	    fprintf(fp, "AAA,interval,%d\n", seconds);
	    fprintf(fp, "AAA,snapshots,%d\n", maxloops);
#ifdef POWER
	    fprintf(fp, "AAA,cpus,%d,%d\n", cpus / lparcfg.smt_mode, cpus);	/* physical CPU, logical CPU */
	    fprintf(fp, "AAA,CPU ID length,3\n");	/* Give analyzer a chance to easily find length of CPU number - 3 digits here! */
#else
	    fprintf(fp, "AAA,cpus,%d\n", cpus);
#endif
#ifdef X86
	    fprintf(fp, "AAA,x86,VendorId,%s\n", vendor_ptr);
	    fprintf(fp, "AAA,x86,ModelName,%s\n", model_ptr);
	    fprintf(fp, "AAA,x86,MHz,%s\n", mhz_ptr);
	    fprintf(fp, "AAA,x86,bogomips,%s\n", bogo_ptr);
	    fprintf(fp, "AAA,x86,ProcessorChips,%d\n", processorchips);
	    fprintf(fp, "AAA,x86,Cores,%d\n", cores);
	    fprintf(fp, "AAA,x86,hyperthreads,%d\n", hyperthreads);
	    fprintf(fp, "AAA,x86,VirtualCPUs,%d\n", cpus);
#endif
#ifdef ARM
	    fprintf(fp, "AAA,ARM,VendorId,%s\n", vendor_ptr);
	    fprintf(fp, "AAA,ARM,ModelName,%s\n", model_ptr);
	    fprintf(fp, "AAA,ARM,MHz,%s\n", mhz_ptr);
	    fprintf(fp, "AAA,ARM,bogomips,%s\n", bogo_ptr);
	    fprintf(fp, "AAA,ARM,ProcessorChips,%d\n", processorchips);
	    fprintf(fp, "AAA,ARM,Cores,%d\n", cores);
	    fprintf(fp, "AAA,ARM,hyperthreads,%d\n", hyperthreads);
	    fprintf(fp, "AAA,ARM,VirtualCPUs,%d\n", cpus);
#endif
	    fprintf(fp, "AAA,proc_stat_variables,%d\n", stat8);
	    fprintf(fp, "AAA,boottime,%s\n", boottime_str);

	    fprintf(fp,
		    "AAA,note0, Warning - use the UNIX sort command to order this file before loading into a spreadsheet\n");
	    fprintf(fp,
		    "AAA,note1, The First Column is simply to get the output sorted in the right order\n");
	    fprintf(fp,
		    "AAA,note2, The T0001-T9999 column is a snapshot number. To work out the actual time; see the ZZZ section at the end\n");
	}
	fflush(NULL);

	for (i = 1; i <= cpus; i++)
	    fprintf(fp,
		    "CPU%03d,CPU %d %s,User%%,Sys%%,Wait%%,Idle%%,Steal%%\n",
		    i, i, run_name);
	fprintf(fp,
		"CPU_ALL,CPU Total %s,User%%,Sys%%,Wait%%,Idle%%,Steal%%,Busy,CPUs\n",
		run_name);
	if (show_mhz) {
	    fprintf(fp, "MHZ,Clock Speed (MHz) %s", run_name);
	    for (i = 1; i <= cpus; i++)
		fprintf(fp, ",CPU%03d", i);
	    fprintf(fp, "\n");
	}
	fprintf(fp,
		"MEM,Memory MB %s,memtotal,hightotal,lowtotal,swaptotal,memfree,highfree,lowfree,swapfree,memshared,cached,active,bigfree,buffers,swapcached,inactive\n",
		run_name);

#ifdef POWER
	proc_lparcfg();
	if (lparcfg.cmo_enabled)
	    fprintf(fp,
		    "MEMAMS,AMS %s,Poolid,Weight,Hypervisor-Page-in/s,HypervisorTime(seconds),not_available_1,not_available_2,not_available_3,Physical-Memory(MB),Page-Size(KB),Pool-Size(MB),Loan-Request(KB)\n",
		    run_name);

#ifdef EXPERIMENTAL
	fprintf(fp,
		"MEMEXPERIMENTAL,New lparcfg numbers %s,DesEntCap,DesProcs,DesVarCapWt,DedDonMode,group,pool,entitled_memory,entitled_memory_group_number,unallocated_entitled_memory_weight,unallocated_io_mapping_entitlement\n",
		run_name);
#endif				/* EXPERIMENTAL */
#endif				/* POWER */

	fprintf(fp,
		"PROC,Processes %s,Runnable,Blocked,pswitch,syscall,read,write,fork,exec,sem,msg\n",
		run_name);
/*
		fprintf(fp,"PAGE,Paging %s,faults,pgin,pgout,pgsin,pgsout,reclaims,scans,cycles\n", run_name);
		fprintf(fp,"FILE,File I/O %s,iget,namei,dirblk,readch,writech,ttyrawch,ttycanch,ttyoutch\n", run_name);
*/


	fprintf(fp, "NET,Network I/O %s", run_name);
	for (i = 0; i < networks; i++)
	    fprintf(fp, ",%-2s-read-KB/s", (char *) p->ifnets[i].if_name);
	for (i = 0; i < networks; i++)
	    fprintf(fp, ",%-2s-write-KB/s", (char *) p->ifnets[i].if_name);
	fprintf(fp, "\n");
	fprintf(fp, "NETPACKET,Network Packets %s", run_name);
	for (i = 0; i < networks; i++)
	    fprintf(fp, ",%-2s-read/s", (char *) p->ifnets[i].if_name);
	for (i = 0; i < networks; i++)
	    fprintf(fp, ",%-2s-write/s", (char *) p->ifnets[i].if_name);
	/* iremoved as it is not below in the BUSY line fprintf(fp,"\n"); */
#ifdef DEBUG
	if (debug)
	    printf("disks=%d x%sx\n", (char *) disks, p->dk[0].dk_name);
#endif	 /*DEBUG*/
	    for (i = 0; i < disks; i++) {
	    if (NEWDISKGROUP(i))
		fprintf(fp, "\nDISKBUSY%s,Disk %%Busy %s", dskgrp(i),
			run_name);
	    fprintf(fp, ",%s", (char *) p->dk[i].dk_name);
	}
	for (i = 0; i < disks; i++) {
	    if (NEWDISKGROUP(i))
		fprintf(fp, "\nDISKREAD%s,Disk Read KB/s %s", dskgrp(i),
			run_name);
	    fprintf(fp, ",%s", (char *) p->dk[i].dk_name);
	}
	for (i = 0; i < disks; i++) {
	    if (NEWDISKGROUP(i))
		fprintf(fp, "\nDISKWRITE%s,Disk Write KB/s %s",
			(char *) dskgrp(i), run_name);
	    fprintf(fp, ",%s", (char *) p->dk[i].dk_name);
	}
	for (i = 0; i < disks; i++) {
	    if (NEWDISKGROUP(i))
		fprintf(fp, "\nDISKXFER%s,Disk transfers per second %s",
			(char *) dskgrp(i), run_name);
	    fprintf(fp, ",%s", p->dk[i].dk_name);
	}
	for (i = 0; i < disks; i++) {
	    if (NEWDISKGROUP(i))
		fprintf(fp, "\nDISKBSIZE%s,Disk Block Size %s", dskgrp(i),
			run_name);
	    fprintf(fp, ",%s", (char *) p->dk[i].dk_name);
	}
	if (extended_disk == 1 && disk_mode == DISK_MODE_DISKSTATS) {
	    for (i = 0; i < disks; i++) {
		if (NEWDISKGROUP(i))
		    fprintf(fp, "\nDISKREADS%s,Disk Rd/s %s", dskgrp(i),
			    run_name);
		fprintf(fp, ",%s", (char *) p->dk[i].dk_name);
	    }
	    for (i = 0; i < disks; i++) {
		if (NEWDISKGROUP(i))
		    fprintf(fp, "\nDISKWRITES%s,Disk Wrt/s %s", dskgrp(i),
			    run_name);
		fprintf(fp, ",%s", (char *) p->dk[i].dk_name);
	    }
	}

	fprintf(fp, "\n");
	list_dgroup(p->dk);
	if(show_jfs) {
    	    jfs_load(LOAD);
    	    fprintf(fp, "JFSFILE,JFS Filespace %%Used %s", hostname);
    	    for (k = 0; k < jfses; k++) {
	        if (jfs[k].mounted && strncmp(jfs[k].name, "/proc", 5)
		    && strncmp(jfs[k].name, "/sys", 4)
		    && strncmp(jfs[k].name, "/run/", 5)
		    && strncmp(jfs[k].name, "/dev/", 5)
		    && strncmp(jfs[k].name, "/var/lib/nfs/rpc", 16)
		    )		/* /proc gives invalid/insane values */
		    fprintf(fp, ",%s", jfs[k].name);
	    }
	    fprintf(fp, "\n");
	    jfs_load(UNLOAD);
	}
#ifdef POWER
	if (proc_lparcfg() && (lparcfg.shared_processor_mode != 0 || lparcfg.DedDonMode > 0)
	    && power_vm_type == VM_POWERVM) {
	    fprintf(fp,
		    "LPAR,Shared CPU LPAR Stats %s,PhysicalCPU,capped,shared_processor_mode,system_potential_processors,system_active_processors,pool_capacity,MinEntCap,partition_entitled_capacity,partition_max_entitled_capacity,MinProcs,Logical CPU,partition_active_processors,partition_potential_processors,capacity_weight,unallocated_capacity_weight,BoundThrds,MinMem,unallocated_capacity,pool_idle_time,smt_mode\n",
		    hostname);

	}
#endif	 /*POWER*/
	    if (show_top) {
	    fprintf(fp, "TOP,%%CPU Utilisation\n");
#ifdef PRE_KERNEL_2_6_18
	    fprintf(fp,
		    "TOP,+PID,Time,%%CPU,%%Usr,%%Sys,Size,ResSet,ResText,ResData,ShdLib,MinorFault,MajorFault,Command\n");
#else
	    fprintf(fp,
		    "TOP,+PID,Time,%%CPU,%%Usr,%%Sys,Size,ResSet,ResText,ResData,ShdLib,MinorFault,MajorFault,Command,Threads,IOwaitTime\n");
#endif
	}
	linux_bbbp("/etc/release", "/bin/cat /etc/*ease 2>/dev/null",
		   WARNING);
	linux_bbbp("lsb_release", "/usr/bin/lsb_release -a 2>/dev/null",
		   WARNING);
	linux_bbbp("fdisk-l", "/sbin/fdisk -l 2>/dev/null", WARNING);
	linux_bbbp("lsblk", "/usr/bin/lsblk 2>/dev/null", WARNING);
	linux_bbbp("lscpu", "/usr/bin/lscpu 2>/dev/null", WARNING);
	linux_bbbp("lshw", "/usr/bin/lshw 2>/dev/null", WARNING);
	linux_bbbp("/proc/cpuinfo", "/bin/cat /proc/cpuinfo 2>/dev/null",
		   WARNING);
	linux_bbbp("/proc/meminfo", "/bin/cat /proc/meminfo 2>/dev/null",
		   WARNING);
	linux_bbbp("/proc/stat", "/bin/cat /proc/stat 2>/dev/null",
		   WARNING);
	linux_bbbp("/proc/version", "/bin/cat /proc/version 2>/dev/null",
		   WARNING);
	linux_bbbp("/proc/net/dev", "/bin/cat /proc/net/dev 2>/dev/null",
		   WARNING);
#ifdef POWER
	/* PowerKVM useful information */
	linux_bbbp("/proc/device-tree/host-model",  
		"/bin/cat /proc/device-tree/host-model 2>/dev/null", WARNING);
	linux_bbbp("/proc/device-tree/host-serial", 
		"/bin/cat /proc/device-tree/host-serial 2>/dev/null", WARNING);
	linux_bbbp("/proc/device-tree/ibm,partition-name", 
		"/bin/cat /proc/device-tree/ibm,partition-name 2>/dev/null", WARNING);

	linux_bbbp("ppc64_utils - lscfg", "/usr/sbin/lscfg 2>/dev/null", WARNING);
	linux_bbbp("ppc64_utils - ls-vdev",
		   "/usr/sbin/ls-vdev 2>/dev/null", WARNING);
	linux_bbbp("ppc64_utils - ls-veth",
		   "/usr/sbin/ls-veth 2>/dev/null", WARNING);
	linux_bbbp("ppc64_utils - ls-vscsi",
		   "/usr/sbin/ls-vscsi 2>/dev/null", WARNING);
	linux_bbbp("ppc64_utils - lsmcode",
		   "/usr/sbin/lsmcode 2>/dev/null", WARNING);
	linux_bbbp("ppc64_cpu - smt",
		   "/usr/sbin/ppc64_cpu --smt 2>/dev/null", WARNING);
	linux_bbbp("ppc64_cpu - cores",
		   "/usr/sbin/ppc64_cpu --cores-present 2>/dev/null", WARNING);
	linux_bbbp("ppc64_cpu - DSCR",
		   "/usr/sbin/ppc64_cpu --dscr 2>/dev/null", WARNING);
	linux_bbbp("ppc64_cpu - snooze",
		   "/usr/sbin/ppc64_cpu --smt-snooze-delay 2>/dev/null", WARNING);
	linux_bbbp("ppc64_cpu - run-mode",
		   "/usr/sbin/ppc64_cpu --run-mode 2>/dev/null", WARNING);
	linux_bbbp("ppc64_cpu - frequency",
		   "/usr/sbin/ppc64_cpu --frequency 2>/dev/null", WARNING);

	linux_bbbp("bootlist -m nmonal -o",
		   "/usr/sbin/bootlist -m normal -o 2>/dev/null", WARNING);
	linux_bbbp("lsslot", "/usr/sbin/lsslot      2>/dev/null", WARNING);
	linux_bbbp("lparstat -i", "/usr/sbin/lparstat -i 2>/dev/null", WARNING);
	linux_bbbp("lsdevinfo", "/usr/sbin/lsdevinfo 2>/dev/null", WARNING);
	linux_bbbp("ls-vdev", "/usr/sbin/ls-vdev  2>/dev/null", WARNING);
	linux_bbbp("ls-veth", "/usr/sbin/ls-veth  2>/dev/null", WARNING);
	linux_bbbp("ls-vscsi", "/usr/sbin/ls-vscsi 2>/dev/null", WARNING);

#endif
	linux_bbbp("/proc/diskinfo", "/bin/cat /proc/diskinfo 2>/dev/null",
		   WARNING);
	linux_bbbp("/proc/diskstats",
		   "/bin/cat /proc/diskstats 2>/dev/null", WARNING);

	linux_bbbp("/sbin/multipath", "/sbin/multipath -l 2>/dev/null",
		   WARNING);
	linux_bbbp("/dev/mapper", "ls -l /dev/mapper 2>/dev/null",
		   WARNING);
	linux_bbbp("/dev/mpath", "ls -l /dev/mpath 2>/dev/null", WARNING);
	linux_bbbp("/dev/dm-*", "ls -l /dev/dm-* 2>/dev/null", WARNING);
	linux_bbbp("/dev/md*", "ls -l /dev/md* 2>/dev/null", WARNING);
	linux_bbbp("/dev/sd*", "ls -l /dev/sd* 2>/dev/null", WARNING);
	linux_bbbp("/proc/partitions",
		   "/bin/cat /proc/partitions 2>/dev/null", WARNING);
	linux_bbbp("/proc/1/stat", "/bin/cat /proc/1/stat 2>/dev/null",
		   WARNING);
#ifdef PRE_KERNEL_2_6_18
	linux_bbbp("/proc/1/statm", "/bin/cat /proc/1/statm 2>/dev/null",
		   WARNING);
#endif
#ifdef MAINFRAME
	linux_bbbp("/proc/sysinfo", "/bin/cat /proc/sysinfo 2>/dev/null",
		   WARNING);
#endif
	linux_bbbp("/proc/net/rpc/nfs",
		   "/bin/cat /proc/net/rpc/nfs 2>/dev/null", WARNING);
	linux_bbbp("/proc/net/rpc/nfsd",
		   "/bin/cat /proc/net/rpc/nfsd 2>/dev/null", WARNING);
	linux_bbbp("/proc/modules", "/bin/cat /proc/modules 2>/dev/null",
		   WARNING);
	linux_bbbp("ifconfig", "/sbin/ifconfig 2>/dev/null", WARNING);
	linux_bbbp("/bin/df-m", "/bin/df -m 2>/dev/null", WARNING);
	linux_bbbp("/bin/mount", "/bin/mount 2>/dev/null", WARNING);
	linux_bbbp("/etc/fstab", "/bin/cat /etc/fstab 2>/dev/null",
		   WARNING);
	linux_bbbp("netstat -r", "/bin/netstat -r 2>/dev/null", WARNING);
	linux_bbbp("uptime", "/usr/bin/uptime  2>/dev/null", WARNING);
	linux_bbbp("getconf PAGESIZE",
		   "/usr/bin/getconf PAGESIZE  2>/dev/null", WARNING);

#ifdef POWER
	linux_bbbp("/proc/ppc64/lparcfg",
		   "/bin/cat /proc/ppc64/lparcfg 2>/dev/null", WARNING);
	linux_bbbp("lscfg-v", "/usr/sbin/lscfg -v 2>/dev/null", WARNING);
#endif
	sleep(1);		/* to get the first stats to cover this one second and avoids divide by zero issues */
    }
    /* To get the pointers setup */
    /* Was already done earlier, DONT'T switch back here to the old pointer! - switcher(); */
    /*checkinput(); */
    clear();
    fflush(NULL);
#ifdef POWER
    lparcfg.timebase = -1;
#endif

    /* Main loop of the code */
    for (loop = 1;; loop++) {
	/* Save the time and work out how long we were actually asleep
	 * Do this as early as possible and close to reading the CPU statistics in /proc/stat
	 */
	p->time = doubletime();
	elapsed = p->time - q->time;
	timer = time(0);
	tim = localtime(&timer);

	/* Get current count of CPU
	 * As side effect /proc/stat is read
	 */
	old_cpus = cpus;
	get_cpu_cnt();
#ifdef POWER
	/* Always get lpar info as well so we can report physical CPU usage
	 * to make data more meaningful. Return value is ignored here, but
	 * remembered in proc_lparcfg() !
	 */
	proc_lparcfg();
#endif

	if (loop <= 3)		/* This stops the nmon causing the cpu peak at startup */
	    for (i = 0; i < max_cpus + 1; i++)
		cpu_peak[i] = 0.0;

	/* Reset the cursor position to top left */
	y = x = 0;

	if (cursed) {		/* Top line */
	    box(stdscr, 0, 0);
	    mvprintw(x, 1, "nmon");
	    mvprintw(x, 6, "%s", VERSION);
	    if (flash_on)
		mvprintw(x, 15, "[H for help]");
	    mvprintw(x, 30, "Hostname=%s", hostname);
	    mvprintw(x, 52, "Refresh=%2.0fsecs ", elapsed);
	    mvprintw(x, 70, "%02d:%02d.%02d",
		     tim->tm_hour, tim->tm_min, tim->tm_sec);
	    wnoutrefresh(stdscr);
	    x = x + 1;

	    if (welcome && getenv("NMON") == 0) {

		COLOUR wattrset(padwelcome, COLOR_PAIR(2));
		mvwprintw(padwelcome, x + 0, 3, "------------------------------");
		mvwprintw(padwelcome, x + 1, 3, " _ __  _ __ ___   ___  _ __    ");
		mvwprintw(padwelcome, x + 2, 3, "| '_ \\| '_ ` _ \\ / _ \\| '_ \\   ");
		mvwprintw(padwelcome, x + 3, 3, "| | | | | | | | | (_) | | | |  ");
		mvwprintw(padwelcome, x + 4, 3, "|_| |_|_| |_| |_|\\___/|_| |_|  ");
		mvwprintw(padwelcome, x + 5, 3, "                              ");
		mvwprintw(padwelcome, x + 6, 3, "------------------------------");

		COLOUR wattrset(padwelcome, COLOR_PAIR(0));
		mvwprintw(padwelcome, x + 1, 40, "For help type H or ...");
		mvwprintw(padwelcome, x + 2, 40, " nmon -?  - hint");
		mvwprintw(padwelcome, x + 3, 40,
			  " nmon -h  - full details");
		mvwprintw(padwelcome, x + 5, 40,
			  "To stop nmon type q to Quit");
		COLOUR wattrset(padwelcome, COLOR_PAIR(1));
#ifdef POWER 
		get_cpu_cnt();
		proc_read(P_CPUINFO);
		/* find the highest MHz */
		for(i=0; i<proc[P_CPUINFO].lines; i++) {
			if(!strncmp("clock",proc[P_CPUINFO].line[i],5)) {
				if( max_speed < atol(&proc[P_CPUINFO].line[i][9]))
					max_speed = atol(&proc[P_CPUINFO].line[i][9]);
			}	
		}

		lscpu_init();

		switch (power_vm_type) {
		case VM_POWERKVM_GUEST:
		    get_cpu_cnt();
#ifdef RHEL7
		    mvwprintw(padwelcome, x + 8, 3, "%s %s", easy[0], easy[1]);
#else
#ifdef SLES113
		    mvwprintw(padwelcome, x + 8, 3, "%s", easy[2]);
#else
		    mvwprintw(padwelcome, x + 8, 3, "%s", easy[3]);
#endif				/* SLES113 */
#endif				/* RHEL7 */
		    mvwprintw(padwelcome, x + 9, 3, "PowerKVM Guest %s",
			      &proc[P_CPUINFO].line[1][7]);
		    mvwprintw(padwelcome, x + 10, 3,
			      "PowerKVM Guest VirtualCPUs=%d LogicalCPUs=%d",
			      (int) lparcfg.partition_active_processors, cpus);
		    mvwprintw(padwelcome, x + 11, 3,
			      "PowerKVM Guest SMT=%d", lparcfg.smt_mode);
		    break;
		case VM_POWERKVM_HOST:
		    mvwprintw(padwelcome, x + 8, 3, "%s", easy[0]);
		    mvwprintw(padwelcome, x + 9, 3, "PowerKVM Host %s",
			      &proc[P_CPUINFO].line[1][7]);
		    mvwprintw(padwelcome, x + 10, 3,
			      "PowerKVM Host owns all %d CPUs & SMT=%d in the Hosting OS",
			      cpus, lscpu.threads);
		    mvwprintw(padwelcome, x + 11, 3, "PowerKVM Host %s",
			      proc[P_CPUINFO].line[proc[P_CPUINFO].lines - 2]);
		    break;
		case VM_NATIVE:
		    mvwprintw(padwelcome, x + 8, 3, "%s", easy[0]);
		    mvwprintw(padwelcome, x + 9, 3, "Native %s",
			      &proc[P_CPUINFO].line[1][7]);
		    mvwprintw(padwelcome, x + 10, 3,
			      "Native owns all %d CPUs & SMT=%d", cpus,
			      lscpu.threads);
		    mvwprintw(padwelcome, x + 11, 3, "Native %s",
			      proc[P_CPUINFO].line[proc[P_CPUINFO].lines - 2]);
		    break;
		default:
		case VM_POWERVM:
#ifdef SLES113
		    mvwprintw(padwelcome, x + 8, 3, "%s %s", easy[0],
			      easy[2]);
#else
#ifdef RHEL7
		    mvwprintw(padwelcome, x + 8, 3, "%s %s", easy[0],
			      easy[1]);
#else
		    mvwprintw(padwelcome, x + 8, 3, "%s", easy[3]);
#endif
#endif
		    mvwprintw(padwelcome, x + 9, 3, "PowerVM %s %s",
			      &proc[P_CPUINFO].line[1][7],
			      &proc[P_CPUINFO].line[proc[P_CPUINFO].lines -
						    1][11]);
		    mvwprintw(padwelcome, x + 10, 3,
			      "PowerVM Entitlement=%-6.2f VirtualCPUs=%d LogicalCPUs=%d",
			      (double) lparcfg.
			      partition_entitled_capacity / 100.0,
			      (int) lparcfg.partition_active_processors,
			      cpus);
		    mvwprintw(padwelcome, x + 11, 3,
			      "PowerVM SMT=%d Capped=%d", lparcfg.smt_mode,
			      lparcfg.capped);
		    break;
		}

		mvwprintw(padwelcome, x + 12, 3,
			  "Processor Clock=%ld MHz %s", max_speed, lscpu.byte_order);
			  /*&proc[P_CPUINFO].line[2][9], lscpu.byte_order);*/

#endif /*POWER*/
#ifdef MAINFRAME
		get_cpu_cnt();
		proc_read(P_CPUINFO);
		lscpu_init();

#ifdef SLES113
		    mvwprintw(padwelcome, x + 8, 3, "%s %s", easy[0],
			      easy[2]);
#else
#ifdef RHEL7
		    mvwprintw(padwelcome, x + 8, 3, "%s %s", easy[0],
			      easy[1]);
#else
		    mvwprintw(padwelcome, x + 8, 3, "%s", easy[3]);
#endif /*RHEL*/
#endif /*SLES*/

		mvwprintw(padwelcome, x + 10, 3,
			      "Mainframe VM %d CPUs & SMT=%d",
			      cpus, lscpu.threads);
		mvwprintw(padwelcome, x + 11, 3,
			      "Mainframe VM Arch %s", lscpu.arch);
		mvwprintw(padwelcome, x + 12, 3,
			  "Processor %s", lscpu.byte_order);
#endif /*MAINFRAME */
#if X86 || ARM
		get_cpu_cnt();
		lscpu_init();
#ifdef RHEL7
		mvwprintw(padwelcome, x + 8, 3, "%s %s", easy[0], easy[1]);
#else 
#ifdef RHEL6
		mvwprintw(padwelcome, x + 8, 3, "%s", easy[1]);
#else
#ifdef SLES113
		mvwprintw(padwelcome, x + 8, 3, "%s %s %s", easy[1], easy[2], easy[3]);
#else
#ifdef UBUNTU
		mvwprintw(padwelcome, x + 8, 3, "%s %s %s", easy[0], easy[1], easy[2]);
#else
		mvwprintw(padwelcome, x + 8, 3, "%s %s", easy[0], easy[2]);
#endif /*UBUNTU */
#endif /*SLES113 */
#endif /*RHEL6 */
#endif /*RHEL7 */
		mvwprintw(padwelcome, x + 9, 3, "Vendor=%s Model=%s", 
			vendor_ptr, model_ptr);
		mvwprintw(padwelcome, x + 10, 3, "MHz=%s bogomips=%s",
			  mhz_ptr, bogo_ptr);
		if (processorchips || cores || hyperthreads || cpus) {
		    if(processorchips != 0) 
			mvwprintw(padwelcome, x + 11, 3, "ProcessorChips=%d", processorchips);
		    if(cores != 0) 
		    mvwprintw(padwelcome, x + 11, 20, "PhysicalCores=%d", cores);
		    if(hyperthreads!= 0) 
		    mvwprintw(padwelcome, x + 12, 3, "Hyperthreads  =%d", hyperthreads);
#ifndef ARM
		    if(cpus != 0) 
		    mvwprintw(padwelcome, x + 12, 20, "VirtualCPUs =%d", cpus);
#endif /* ARM */
		}
		    mvwprintw(padwelcome, x + 10, 42, "lscpu:CPU=%d %s", lscpu.cpus, lscpu.byte_order);
		    mvwprintw(padwelcome, x + 11, 42, "      Sockets=%d Cores=%d Thrds=%d", lscpu.sockets, lscpu.cores, lscpu.threads);
		    mvwprintw(padwelcome, x + 12, 42, "      MHz=%d max=%d min=%d", lscpu.mhz, lscpu.mhz_max, lscpu.mhz_min);

	
#endif
		COLOUR wattrset(padwelcome, COLOR_PAIR(0));
		mvwprintw(padwelcome, x + 14, 3,
			  "Use these keys to toggle statistics on/off:");
		mvwprintw(padwelcome, x + 15, 3, "  c = CPU         l = CPU Long-term     - = Faster screen updates");
		mvwprintw(padwelcome, x + 16, 3, "  C = \" WideView  U = Utilisation       + = Slower screen updates");
		mvwprintw(padwelcome, x + 17, 3, "  m = Memory      V = Virtual memory    j = File Systems");
		mvwprintw(padwelcome, x + 18, 3, "  d = Disks       n = Network           . = only busy disks/procs");
		mvwprintw(padwelcome, x + 19, 3, "  r = Resource    N = NFS               h = more options");
		mvwprintw(padwelcome, x + 20, 3, "  k = Kernel      t = Top-processes     q = Quit");
		pnoutrefresh(padwelcome, 0, 0, x, 1, LINES - 2, COLS - 2);
		wnoutrefresh(stdscr);
		x = x + 22;
	    }
	} else {
	    if (!cursed && nmon_snap && (loop % nmon_one_in) == 0) {
		child_start(CHLD_SNAP, nmon_snap, time_stamp_type, loop,
			    timer);
	    }


	    if (!show_rrd)
		fprintf(fp, "ZZZZ,%s,%02d:%02d:%02d,%02d-%s-%4d\n", LOOP,
			tim->tm_hour, tim->tm_min, tim->tm_sec,
			tim->tm_mday, month[tim->tm_mon],
			tim->tm_year + 1900);
	    fflush(NULL);
	}
	if (show_verbose && cursed) {
	    BANNER(padverb, "Verbose Mode");
	    mvwprintw(padverb, 1, 0,
		      " Code    Resource            Stats   Now\tWarn\tDanger ");
	    /*      DISPLAY(padverb,7); */
	    /* move(x,0); */
	    x = x + 6;
	}
	if (show_help && cursed) {

	    COLOUR wattrset(padhelp, COLOR_PAIR(2));
	    BANNER(padhelp,
		   "HELP: Hit h to remove this Info   Hit q to Quit");
	    mvwprintw(padhelp, 1, 1,
		      "Letters which toggle on/off statistics:");
	    mvwprintw(padhelp, 2, 1,
		      "h = This help                         | r = Resources OS & Proc");
	    mvwprintw(padhelp, 3, 1,
		      "c = CPU Util  C = wide view           | l = longer term CPU averages");
	    mvwprintw(padhelp, 4, 1,
		      "m = Memory & Swap    L=Huge           | V = Virtual Memory");
	    mvwprintw(padhelp, 5, 1,
		      "n = Network                           | N = NFS");
	    mvwprintw(padhelp, 6, 1,
		      "d = Disk I/O Graphs  D=Stats          | o = Disks %%Busy Map");
	    mvwprintw(padhelp, 7, 1,
		      "k = Kernel stats & loadavg            | j = Filesystem Usage J=reduced");
	    mvwprintw(padhelp, 8, 1, "M = MHz by thread & CPU");
#ifdef NVIDIA_GPU
	    mvwprintw(padhelp, 8, 39, "| a = Accelerator Nvidia GPU ");
#else				/*NVIDIA_GPU */
#ifdef POWER
	    mvwprintw(padhelp, 8, 39, "| p = if(PowerVM) LPAR details");
#endif	     /*POWER*/
#endif				/*NVIDIA_GPU */
		mvwprintw(padhelp, 9, 1,
			  "t = TopProcess 1=Priority/Nice/State  | u = TopProc with command line");
	    mvwprintw(padhelp, 10, 1,
		      "    ReOrder by: 3=CPU 4=RAM 5=I/O     |     Hit u twice to update");
	    mvwprintw(padhelp, 11, 1,
		      "g = User Defined Disk Groups          | G = with -g switches Disk graphs");
	    mvwprintw(padhelp, 12, 1,
		      "    [start nmon with -g <filename>]   |     to disk groups only");
	    mvwprintw(padhelp, 13, 39, "| b = black & white mode");
	    mvwprintw(padhelp, 14, 1,
		      "Other Controls:                       |");
	    mvwprintw(padhelp, 15, 1,
		      "+ = double the screen refresh time    | 0 = reset peak marks (\">\") to zero");
	    mvwprintw(padhelp, 16, 1,
		      "- = half   the screen refresh time    | space refresh screen now");
	    mvwprintw(padhelp, 17, 1,
		      ". = Display only busy disks & CPU     | q = Quit");
/*			mvwprintw(padhelp,18, 1, "v = Verbose Simple Checks - OK/Warnings/Danger"); */

	    mvwprintw(padhelp, 19, 1,
		"(C) Copyright 2009 Nigel Griffiths    | See http://nmon.sourceforge.net");
	    mvwprintw(padhelp, 20, 1, "Colour:");
	    for (i = 0; i < 13; i++) {
		COLOUR wattrset(padhelp, COLOR_PAIR(i));
		mvwprintw(padhelp, 20, 8 + i * 5, "#%d#", i);
	    }
	    COLOUR wattrset(padhelp, COLOR_PAIR(0));
	    DISPLAY(padhelp, 21);

	}
/* for debugging use only
		if(error_on && errorstr[0] != 0) {
			mvprintw(x, 0, "Error: %s  ",errorstr);
			x = x + 1;
		}
*/
	if (show_res && cursed) {
	    proc_read(P_CPUINFO);
	    proc_read(P_VERSION);

	    BANNER(padres, "Resources Linux & Processor");
	    COLOUR wattrset(padres, COLOR_PAIR(2));
	    mvwprintw(padres, 1, 4, "Linux: %s", proc[P_VERSION].line[0]);
	    mvwprintw(padres, 2, 4, "Build: %s", proc[P_VERSION].line[1]);
	    mvwprintw(padres, 3, 4, "Release  : %s", uts.release);
	    mvwprintw(padres, 4, 4, "Version  : %s", uts.version);
	    COLOUR wattrset(padres, COLOR_PAIR(3));
#ifdef POWER
	    mvwprintw(padres, 5, 4, "cpuinfo: %s",
		      proc[P_CPUINFO].line[1]);
	    mvwprintw(padres, 6, 4, "cpuinfo: %s",
		      proc[P_CPUINFO].line[2]);
	    mvwprintw(padres, 7, 4, "cpuinfo: %s",
		      proc[P_CPUINFO].line[3]);
	    mvwprintw(padres, 8, 4, "cpuinfo: %s    %s",
		      proc[P_CPUINFO].line[proc[P_CPUINFO].lines - 2],
		      proc[P_CPUINFO].line[proc[P_CPUINFO].lines - 1]);
	    /* needs lparcfg to be already processed */
	    proc_lparcfg();
	    switch (power_vm_type) {
	    case VM_POWERKVM_GUEST:
		mvwprintw(padres, 9, 20,
			  "PowerKVM Guest Physical CPU:%d & Virtual CPU (SMT):%d  %s",
			  lparcfg.partition_active_processors, cpus,
			  lscpu.byte_order);
		break;
	    case VM_POWERKVM_HOST:
		mvwprintw(padres, 9, 20,
			  "PowerKVM Host Physical CPU:%d  %s", cpus,
			  lscpu.byte_order);
		break;
	    case VM_POWERVM:
		mvwprintw(padres, 9, 20,
			  "PowerVM Physical CPU:%d & Logical CPU:%d  %s",
			  lparcfg.partition_active_processors, cpus,
			  lscpu.byte_order);
		break;
	    case VM_NATIVE:
		mvwprintw(padres, 9, 20, "Native Mode Physical CPU:%d  %s",
			  cpus, lscpu.byte_order);
		break;
	    }
#endif /* POWER */
#ifdef MAINFRAME
	    mvwprintw(padres, 5, 4, "cpuinfo: %s",
		      proc[P_CPUINFO].line[1]);
	    mvwprintw(padres, 6, 4, "cpuinfo: %s",
		      proc[P_CPUINFO].line[2]);
	    mvwprintw(padres, 7, 4, "cpuinfo: %s",
		      proc[P_CPUINFO].line[3]);
	    mvwprintw(padres, 8, 4, "cpuinfo: %s",
		      proc[P_CPUINFO].line[4]);
#endif/* MAINFRAME */
#ifdef X86 
	    mvwprintw(padres, 5, 4, "cpuinfo: Vendor=%s Model=%s", vendor_ptr, model_ptr);
	    mvwprintw(padres, 6, 4, "cpuinfo: Hz=%s bogomips=%s", mhz_ptr, bogo_ptr);

	    if (processorchips || cores || hyperthreads || cpus) {
		mvwprintw(padres, 7, 4,
			  "cpuinfo: ProcessorChips=%d PhysicalCores=%d",
			  processorchips, cores);
		mvwprintw(padres, 8, 4,
			  "cpuinfo: Hyperthreads  =%d VirtualCPUs =%d",
			  hyperthreads, cpus);
	    }
#endif /* X86 */
#ifdef ARM
	    mvwprintw(padres, 5, 4, "cpuinfo: Vendor=%s Model=%s BogoMIPS=%s", vendor_ptr, model_ptr, bogo_ptr);
            mvwprintw(padres, 6, 4, "lscpu: CPU=%d %s", lscpu.cpus, lscpu.byte_order);
            mvwprintw(padres, 7, 4, "lscpu: Sockets=%d Cores=%d Thrds=%d", lscpu.sockets, lscpu.cores, lscpu.threads);
            mvwprintw(padres, 8, 4, "lscpu: max=%d min=%d", lscpu.mhz_max, lscpu.mhz_min);

#endif /* ARM */
	    mvwprintw(padres, 9, 4, "# of CPUs: %d", cpus);
	    COLOUR wattrset(padres, COLOR_PAIR(5));
	    mvwprintw(padres, 10, 4, "Machine  : %s", uts.machine);
	    mvwprintw(padres, 11, 4, "Nodename : %s", uts.nodename);
	    COLOUR wattrset(padres, COLOR_PAIR(6));
	    mvwprintw(padres, 12, 4, "/etc/*ease[1]: %s", easy[0]);
	    mvwprintw(padres, 13, 4, "/etc/*ease[2]: %s", easy[1]);
	    mvwprintw(padres, 14, 4, "/etc/*ease[3]: %s", easy[2]);
	    mvwprintw(padres, 15, 4, "/etc/*ease[4]: %s", easy[3]);
	    COLOUR wattrset(padres, COLOR_PAIR(2));
	    mvwprintw(padres, 16, 4, "lsb_release: %s", lsb_release[0]);
	    mvwprintw(padres, 17, 4, "lsb_release: %s", lsb_release[1]);
	    mvwprintw(padres, 18, 4, "lsb_release: %s", lsb_release[2]);
	    mvwprintw(padres, 19, 4, "lsb_release: %s", lsb_release[3]);
	    COLOUR wattrset(padres, COLOR_PAIR(0));
	    DISPLAY(padres, 20);
	}
	if (show_longterm) {
	    proc_read(P_STAT);
	    proc_cpu();
	    cpu_user = RAWTOTAL(user) + RAWTOTAL(nice);
	    cpu_sys =
		RAWTOTAL(sys) + RAWTOTAL(irq) + RAWTOTAL(softirq) ;
		/* + RAWTOTAL(guest) + RAWTOTAL(guest_nice); these are in addition to the 100% */
	    cpu_wait = RAWTOTAL(wait);
	    cpu_idle = RAWTOTAL(idle);
	    cpu_steal = RAWTOTAL(steal);
	    /* DEBUG inject steal       cpu_steal = cpu_sys; */
	    cpu_sum = cpu_idle + cpu_user + cpu_sys + cpu_wait + cpu_steal;

	    save_snap((double) cpu_user / (double) cpu_sum * 100.0,
		      (double) cpu_sys / (double) cpu_sum * 100.0,
		      (double) cpu_wait / (double) cpu_sum * 100.0,
		      (double) cpu_idle / (double) cpu_sum * 100.0,
		      (double) cpu_steal / (double) cpu_sum * 100.0);
	    plot_snap(padlong);
	    DISPLAY(padlong, MAX_SNAP_ROWS + 2);
	}
	if (show_smp || show_verbose || show_wide) {
	    proc_read(P_STAT);
	    proc_cpu();
	    if (cpus > max_cpus && !cursed) {
		for (i = max_cpus + 1; i <= cpus; i++)
		    fprintf(fp,
			    "CPU%03d,CPU %d %s,User%%,Sys%%,Wait%%,Idle%%\n",
			    i, i, run_name);
		max_cpus = cpus;
	    }
	    if (old_cpus != cpus) {
		if (!cursed) {
		    if (bbbr_line == 0) {
			fprintf(fp, "BBBR,0,Reconfig,action,old,new\n");
			bbbr_line++;
		    }
		    fprintf(fp, "BBBR,%03d,%s,cpuchg,%d,%d\n", bbbr_line++,
			    LOOP, old_cpus, cpus);
		} else {
		    /* wmove(padsmp,0,0); */
		    /* doesn't work CURSE wclrtobot(padsmp); */
		    /* Do BRUTE force overwrite of previous data */
		    if (cpus < old_cpus) {
			for (i = cpus; i < old_cpus; i++)
			    mvwprintw(padsmp, i + 4, 0,
				      "                                                                                    ");
		    }
		}
	    }
	    if (show_smp) {
		if (cursed) {
		    BANNER(padsmp, "CPU Utilisation");

		    /* mvwprintw(padsmp,1, 0, cpu_line); */
		    /*
		     *mvwprintw(padsmp,2, 0, "CPU  User%%  Sys%% Wait%% Idle|0          |25         |50          |75       100|");
		     */
		    mvwprintw(padsmp, 1, 0, cpu_line);
		    mvwprintw(padsmp, 2, 0, "CPU  ");
		    COLOUR wattrset(padsmp, COLOR_PAIR(2));	/* Green */
		    mvwprintw(padsmp, 2, 4, "User%%");
		    COLOUR wattrset(padsmp, COLOR_PAIR(1));	/* Red */
		    mvwprintw(padsmp, 2, 9, "  Sys%%");
		    COLOUR wattrset(padsmp, COLOR_PAIR(4));	/* Blue */
		    mvwprintw(padsmp, 2, 15, " Wait%%");
		    if (p->cpu_total.steal != q->cpu_total.steal) {
			COLOUR wattrset(padsmp, COLOR_PAIR(5));
			mvwprintw(padsmp, 2, 22, "Steal");
		    } else {
			COLOUR wattrset(padsmp, COLOR_PAIR(0));
			mvwprintw(padsmp, 2, 22, " Idle");
		    }
		    COLOUR wattrset(padsmp, COLOR_PAIR(0));
		    mvwprintw(padsmp, 2, 27,
			      "|0          |25         |50          |75       100|");
		}		/* if (show_smp) AND if(cursed) */
#ifdef POWER
		/* Always get lpar info as well so we can report physical CPU usage
		 * to make data more meaningful
		 * This assumes that LPAR info is available in q and p !
		 */
		if (proc_lparcfg() > 0) {
		    if (lparcfg.shared_processor_mode == 1) {
			if (lparcfg.timebase == -1) {
			    lparcfg.timebase = 0;
			    proc_read(P_CPUINFO);
			    for (i = 0; i < proc[P_CPUINFO].lines - 1; i++) {
				if (!strncmp
				    ("timebase", proc[P_CPUINFO].line[i],
				     8)) {
				    sscanf(proc[P_CPUINFO].line[i],
					   "timebase : %lld",
					   &lparcfg.timebase);
				    break;
				}
			    }
			} else {
			    /* PowerKVM Host or Guest or Native have not Entitlement stats */
			    if (power_vm_type == VM_POWERVM)
				mvwprintw(padsmp, 1, 30,
					  "EntitledCPU=% 6.3f",
					  (double) lparcfg.
					  partition_entitled_capacity /
					  100.0);
			    /* Only if the calculation is working */
			    if (lparcfg.purr_diff != 0)
				mvwprintw(padsmp, 1, 50,
					  "PhysicalCPUused=% 7.3f",
					  (double) lparcfg.purr_diff /
					  (double) lparcfg.timebase /
					  elapsed);
			}
		    }
		}
#endif
		for (i = 0; i < cpus; i++) {
		    cpu_user = RAW(user) + RAW(nice);
		    cpu_sys =
			RAW(sys) + RAW(irq) + RAW(softirq); 
			/* + RAW(guest) + RAW(guest_nice); these are in addition to the 100% */
		    cpu_wait = RAW(wait);
		    cpu_idle = RAW(idle);
		    cpu_steal = RAW(steal);
/* DEBUG inject steal       cpu_steal = cpu_sys; */
		    cpu_sum =
			cpu_idle + cpu_user + cpu_sys + cpu_wait +
			cpu_steal;
		    /* Check if we had a CPU # change and have to set idle to 100 */
		    if (cpu_sum == 0)
			cpu_sum = cpu_idle = 100.0;
		    if (smp_first_time && cursed) {
			if (i == 0)
			    mvwprintw(padsmp, 3 + i, 27,
				      "| Please wait gathering CPU statistics");
			else
			    mvwprintw(padsmp, 3 + i, 27, "|");
			mvwprintw(padsmp, 3 + i, 77, "|");
		    } else {
#ifdef POWER
			/* lparcfg gathered above */
			if (lparcfg.smt_mode > 1
			    && i % lparcfg.smt_mode == 0) {
			    mvwprintw(padsmp, 3 + i, 27, "*");
			    mvwprintw(padsmp, 3 + i, 77, "*");
			}
#endif
			plot_smp(padsmp, i + 1, 3 + i,
				 (double) cpu_user / (double) cpu_sum *
				 100.0,
				 (double) cpu_sys / (double) cpu_sum *
				 100.0,
				 (double) cpu_wait / (double) cpu_sum *
				 100.0,
				 (double) cpu_idle / (double) cpu_sum *
				 100.0,
				 (double) cpu_steal / (double) cpu_sum *
				 100.0);
#ifdef POWER
			/* lparcfg gathered above */
			if (lparcfg.smt_mode > 1
			    && i % lparcfg.smt_mode == 0) {
			    mvwprintw(padsmp, 3 + i, 27, "*");
			    mvwprintw(padsmp, 3 + i, 77, "*");
			}
#endif

			RRD fprintf(fp,
				    "rrdtool update cpu%02d.rrd %s:%.1f:%.1f:%.1f:%.1f\n",
				    i, LOOP,
				    (double) cpu_user / (double) cpu_sum *
				    100.0,
				    (double) cpu_sys / (double) cpu_sum *
				    100.0,
				    (double) cpu_wait / (double) cpu_sum *
				    100.0,
				    (double) cpu_idle / (double) cpu_sum *
				    100.0);
		    }
		}		/* for (i = 0; i < cpus; i++) */
		CURSE mvwprintw(padsmp, i + 3, 0, cpu_line);
#ifdef POWER
		/* proc_lparcfg called above in previous ifdef
		 */
		if (lparcfg.shared_processor_mode == 1) {
		    if (lparcfg.timebase == -1) {
			lparcfg.timebase = 0;
			proc_read(P_CPUINFO);
			for (i = 0; i < proc[P_CPUINFO].lines - 1; i++) {
			    if (!strncmp
				("timebase", proc[P_CPUINFO].line[i], 8)) {
				sscanf(proc[P_CPUINFO].line[i],
				       "timebase : %lld",
				       &lparcfg.timebase);
				break;
			    }
			}
		    } else {
			mvwprintw(padsmp, i + 3, 29, "%s",
				  lparcfg.
				  shared_processor_mode ? "Shared" :
				  "Dedicated");
			mvwprintw(padsmp, i + 3, 39, "|");
			/* PowerKVM has no Capped concept */
			if (power_vm_type == VM_POWERVM)
			    mvwprintw(padsmp, i + 3, 41, "%s",
				      lparcfg.
				      capped ? "--Capped" : "Uncapped");
			mvwprintw(padsmp, i + 3, 51, "|");
			mvwprintw(padsmp, i + 3, 54, "SMT=%d",
				  lparcfg.smt_mode);
			mvwprintw(padsmp, i + 3, 64, "|");
			mvwprintw(padsmp, i + 3, 67, "VP=%.0f",
				  (float) lparcfg.
				  partition_active_processors);
		    }
		}
#endif
		cpu_user = RAWTOTAL(user) + RAWTOTAL(nice);
		cpu_sys =
		    RAWTOTAL(sys) + RAWTOTAL(irq) + RAWTOTAL(softirq);
		    /* + RAWTOTAL(guest) + RAWTOTAL(guest_nice); these are in addition to the 100% */
		cpu_wait = RAWTOTAL(wait);
		cpu_idle = RAWTOTAL(idle);
		cpu_steal = RAWTOTAL(steal);
/* DEBUG inject steal       cpu_steal = cpu_sys; */
		cpu_sum =
		    cpu_idle + cpu_user + cpu_sys + cpu_wait + cpu_steal;

		/* Check if we had a CPU # change and have to set idle to 100 */
		if (cpu_sum == 0)
		    cpu_sum = cpu_idle = 100.0;

		RRD fprintf(fp,
			    "rrdtool update cpu.rrd %s:%.1f:%.1f:%.1f:%.1f%.1f\n",
			    LOOP,
			    (double) cpu_user / (double) cpu_sum * 100.0,
			    (double) cpu_sys / (double) cpu_sum * 100.0,
			    (double) cpu_wait / (double) cpu_sum * 100.0,
			    (double) cpu_idle / (double) cpu_sum * 100.0,
			    (double) cpu_steal / (double) cpu_sum * 100.0);
		if (cpus > 1 || !cursed) {
		    if (!smp_first_time || !cursed) {
			plot_smp(padsmp, 0, 4 + i,
				 (double) cpu_user / (double) cpu_sum *
				 100.0,
				 (double) cpu_sys / (double) cpu_sum *
				 100.0,
				 (double) cpu_wait / (double) cpu_sum *
				 100.0,
				 (double) cpu_idle / (double) cpu_sum *
				 100.0,
				 (double) cpu_steal / (double) cpu_sum *
				 100.0);
		    }

		    CURSE mvwprintw(padsmp, i + 5, 0, cpu_line);
		    i = i + 2;
		}		/* if (cpus > 1 || !cursed) */
		smp_first_time = 0;
		DISPLAY(padsmp, i + 4);
	    }			/* if (show_smp)  */
	    if (show_wide) {
		if (cursed) {
		    int rows = 0;
		    BANNER(padwide, "CPU Utilisation Wide View");
		    char *wide1 =
			"100%%-+--------+---------+---------+---------+---------+---------+-----+100%%";
		    char *wide2 =
			" 90%%-|                                                                |-90%%";
		    char *wide3 =
			" 80%%-|                                                                |-80%%";
		    char *wide4 =
			" 70%%-|                                                                |-70%%";
		    char *wide5 =
			" 60%%-|                                                                |-60%%";
		    char *wide6 =
			" 50%%-|                                                                |-50%%";
		    char *wide7 =
			" 40%%-|                                                                |-40%%";
		    char *wide8 =
			" 30%%-|                                                                |-30%%";
		    char *wide9 =
			" 20%%-|                                                                |-20%%";
		    char *wide10 =
			" 10%%-|                                                                |-10%%";

		    mvwprintw(padwide, 1, 0, wide1);
		    mvwprintw(padwide, 2, 0, wide2);
		    mvwprintw(padwide, 3, 0, wide3);
		    mvwprintw(padwide, 4, 0, wide4);
		    mvwprintw(padwide, 5, 0, wide5);
		    mvwprintw(padwide, 6, 0, wide6);
		    mvwprintw(padwide, 7, 0, wide7);
		    mvwprintw(padwide, 8, 0, wide8);
		    mvwprintw(padwide, 9, 0, wide9);
		    mvwprintw(padwide, 10, 0, wide10);
		    mvwprintw(padwide, 11, 0,
			      " CPU +1--------+10-------+20-------+30-------+40-------+50-------+60--+--0%%");
		    mvwprintw(padwide, 1, 6, "CPU(s)=%d", cpus);
		    if (wide_first_time) {
			mvwprintw(padwide, 3, 7,
				  " Please wait gathering CPU statistics");
		    } else {
			for (i = 0; i < cpus && i < 64; i++) {
			    cpu_user = RAW(user) + RAW(nice);
			    cpu_sys =
				RAW(sys) + RAW(irq) + RAW(softirq);
				/* + RAW(guest) + RAW(guest_nice); these are in addition to the 100% */
			    cpu_sum = cpu_user + cpu_sys;
			    COLOUR wattrset(padwide, COLOR_PAIR(4));	/* blue */
			    if (i % 2) {
				mvwprintw(padwide, 6, 6 + i, ".");
			    }
			    if (cpu_sum > 75) {
				COLOUR wattrset(padwide, COLOR_PAIR(1));	/*red */
			    } else {
				if (cpu_sum > 50) {
				    COLOUR wattrset(padwide, COLOR_PAIR(5));	/*magenta */
				} else {
				    COLOUR wattrset(padwide, COLOR_PAIR(2));	/*green */
				}
			    }
			    for (j = 1, k = 10; j < 10; j++, k--)
				if (cpu_sum > j * 10.0)
				    mvwprintw(padwide, k, 6 + i, "#");
			    COLOUR wattrset(padwide, COLOR_PAIR(0));	/* white */
			    if (0.1 < cpu_sum && cpu_sum < 5.0)
				mvwprintw(padwide, 10, 6 + i, ".");
			    if (5.1 <= cpu_sum && cpu_sum < 10.0)
				mvwprintw(padwide, 10, 6 + i, "o");
			}
			if (cpus < 64)
			    for (j = 2; j <= 10; j++)
				mvwprintw(padwide, j, 6 + i, "|");
			rows = 12;
		    }
		    if (cpus > 63) {
			mvwprintw(padwide, rows + 0, 0, wide1);
			mvwprintw(padwide, rows + 1, 0, wide2);
			mvwprintw(padwide, rows + 2, 0, wide3);
			mvwprintw(padwide, rows + 3, 0, wide4);
			mvwprintw(padwide, rows + 4, 0, wide5);
			mvwprintw(padwide, rows + 5, 0, wide6);
			mvwprintw(padwide, rows + 6, 0, wide7);
			mvwprintw(padwide, rows + 7, 0, wide8);
			mvwprintw(padwide, rows + 8, 0, wide9);
			mvwprintw(padwide, rows + 9, 0, wide10);
			mvwprintw(padwide, rows + 10, 0,
				  " CPU +65---+70-------+80-------+90-------+100------+110------+120-----+--0%%");
			if (wide_first_time) {
			    mvwprintw(padwide, rows + 3, 7,
				      " Please wait gathering CPU statistics");
			} else {
			    for (i = 64; i < cpus && i < 128; i++) {
				cpu_user = RAW(user) + RAW(nice);
				cpu_sys =
				    RAW(sys) + RAW(irq) + RAW(softirq);
				    /* + RAW(guest) + RAW(guest_nice); these are in addition to the 100% */
				cpu_sum = cpu_user + cpu_sys;
				COLOUR wattrset(padwide, COLOR_PAIR(4));	/* blue */
				if (i % 2) {
				    mvwprintw(padwide, rows + 5,
					      6 + i - 64, ".");
				}
				if (cpu_sum > 75) {
				    COLOUR wattrset(padwide, COLOR_PAIR(1));	/*red */
				} else {
				    if (cpu_sum > 50) {
					COLOUR wattrset(padwide, COLOR_PAIR(5));	/*magenta */
				    } else {
					COLOUR wattrset(padwide, COLOR_PAIR(2));	/*green */
				    }
				}
				for (j = 1, k = rows + 9; j < 10; j++, k--)
				    if (cpu_sum > j * 10.0)
					mvwprintw(padwide, k, 6 + i - 64,
						  "#");
				COLOUR wattrset(padwide, COLOR_PAIR(0));	/* white */
				if (0.1 < cpu_sum && cpu_sum < 5.0)
				    mvwprintw(padwide, rows + 9,
					      6 + i - 64, ".");
				if (5.1 <= cpu_sum && cpu_sum < 10.0)
				    mvwprintw(padwide, rows + 9,
					      6 + i - 64, "o");
			    }

			    if (cpus < 128)
				COLOUR wattrset(padwide, COLOR_PAIR(4));	/* blue */
			    for (j = rows; j <= rows + 9; j++)
				mvwprintw(padwide, j, 6 + i - 64, "<");
			    COLOUR wattrset(padwide, COLOR_PAIR(0));	/* white */
			}
			rows = 23;
		    }
		    if (cpus > 127) {
			mvwprintw(padwide, rows + 0, 0, wide1);
			mvwprintw(padwide, rows + 1, 0, wide2);
			mvwprintw(padwide, rows + 2, 0, wide3);
			mvwprintw(padwide, rows + 3, 0, wide4);
			mvwprintw(padwide, rows + 4, 0, wide5);
			mvwprintw(padwide, rows + 5, 0, wide6);
			mvwprintw(padwide, rows + 6, 0, wide7);
			mvwprintw(padwide, rows + 7, 0, wide8);
			mvwprintw(padwide, rows + 8, 0, wide9);
			mvwprintw(padwide, rows + 9, 0, wide10);
			mvwprintw(padwide, rows + 10, 0,
				  " CPU +129--------+140------+150------+160------+170------+180------+190--0%%");
			if (wide_first_time) {
			    mvwprintw(padwide, rows + 3, 7,
				      " Please wait gathering CPU statistics");
			} else {
			    for (i = 128; i < cpus && i < 196; i++) {
				cpu_user = RAW(user) + RAW(nice);
				cpu_sys =
				    RAW(sys) + RAW(irq) + RAW(softirq);
				    /* + RAW(guest) + RAW(guest_nice); these are in addition of the 100% */
				cpu_sum = cpu_user + cpu_sys;
				COLOUR wattrset(padwide, COLOR_PAIR(4));	/* blue */
				if (i % 2) {
				    mvwprintw(padwide, rows + 5,
					      6 + i - 128, ".");
				}
				if (cpu_sum > 75) {
				    COLOUR wattrset(padwide, COLOR_PAIR(1));	/*red */
				} else {
				    if (cpu_sum > 50) {
					COLOUR wattrset(padwide, COLOR_PAIR(5));	/*magenta */
				    } else {
					COLOUR wattrset(padwide, COLOR_PAIR(2));	/*green */
				    }
				}
				for (j = 1, k = rows + 9; j < 10; j++, k--)
				    if (cpu_sum > j * 10.0)
					mvwprintw(padwide, k, 6 + i - 128,
						  "#");
				COLOUR wattrset(padwide, COLOR_PAIR(0));	/* white */
				if (0.1 < cpu_sum && cpu_sum < 5.0)
				    mvwprintw(padwide, rows + 9,
					      6 + i - 128, ".");
				if (5.1 <= cpu_sum && cpu_sum < 10.0)
				    mvwprintw(padwide, rows + 9,
					      6 + i - 128, "o");
			    }

			    if (cpus < 196)
				COLOUR wattrset(padwide, COLOR_PAIR(4));	/* blue */
			    for (j = rows; j <= rows + 9; j++)
				mvwprintw(padwide, j, 6 + i - 128, "<");
			    COLOUR wattrset(padwide, COLOR_PAIR(0));	/* white */
			}
			rows = 34;
		    }
		    wide_first_time = 0;
		    DISPLAY(padwide, rows);
		}
		proc_read(P_STAT);
		proc_cpu();

		if (show_verbose && cursed) {
		    cpu_user = RAWTOTAL(user) + RAWTOTAL(nice);
		    cpu_sys =
			RAWTOTAL(sys) + RAWTOTAL(irq) + RAWTOTAL(softirq);
			/* + RAWTOTAL(guest) + RAWTOTAL(guest_nice); these are in addition to the 100% */
		    cpu_wait = RAWTOTAL(wait);
		    cpu_idle = RAWTOTAL(idle) + RAWTOTAL(steal);
		    cpu_sum = cpu_idle + cpu_user + cpu_sys + cpu_wait;

		    cpu_busy =
			(double) (cpu_user +
				  cpu_sys) / (double) cpu_sum *100.0;
		    mvwprintw(padverb, 2, 0,
			      "        -> CPU               %%busy %5.1f%%\t>80%%\t>90%%          ",
			      cpu_busy);
		    if (cpu_busy > 90.0) {
			COLOUR wattrset(padverb, COLOR_PAIR(1));
			mvwprintw(padverb, 2, 0, " DANGER");
		    } else if (cpu_busy > 80.0) {
			COLOUR wattrset(padverb, COLOR_PAIR(4));
			mvwprintw(padverb, 2, 0, "Warning");
		    } else {
			COLOUR wattrset(padverb, COLOR_PAIR(2));
			mvwprintw(padverb, 2, 0, "     OK");
		    }
		    COLOUR wattrset(padverb, COLOR_PAIR(0));
		}

	    }			/* if (cursed) */
	}			/* if (show_smp || show_verbose) */
	if (show_util) {
	    proc_read(P_STAT);
	    proc_cpu();
	    if (cursed) {
		BANNER(padutil, "CPU Utilisation Stats");
		mvwprintw(padutil, 2, 0, "CPU");
		for (i = 0; i < cpus; i++)
		    mvwprintw(padutil, 3 + i, 0, "%3d", i + 1);
		mvwprintw(padutil, 1, 0, "ALL");
		if (first_util) {
		    mvwprintw(padutil, 5, 27,
			      " Please wait gathering CPU statistics");
		} else {
		    COLOUR wattrset(padutil, COLOR_PAIR(2));	/* Green */
		    mvwprintw(padutil, 2, 4, "  User%%");
		    for (i = 0; i < cpus; i++)
			mvwprintw(padutil, 3 + i, 4, "%7.1f",
				  RAW(user) / elapsed);
		    mvwprintw(padutil, 1, 4, "%7.1f",
			      RAWTOTAL(user) / elapsed);
		    mvwprintw(padutil, 2, 11, "  Nice%%");
		    for (i = 0; i < cpus; i++)
			mvwprintw(padutil, 3 + i, 11, "%7.1f",
				  RAW(nice) / elapsed);
		    mvwprintw(padutil, 1, 11, "%7.1f",
			      RAWTOTAL(nice) / elapsed);

		    COLOUR wattrset(padutil, COLOR_PAIR(1));	/* Red */
		    mvwprintw(padutil, 2, 18, "   Sys%%");
		    for (i = 0; i < cpus; i++)
			mvwprintw(padutil, 3 + i, 18, "%7.1f",
				  RAW(sys) / elapsed);
		    mvwprintw(padutil, 1, 18, "%7.1f",
			      RAWTOTAL(sys) / elapsed);

		    COLOUR wattrset(padutil, COLOR_PAIR(3));	/* Yellow */
		    mvwprintw(padutil, 2, 25, "  Idle%%");
		    for (i = 0; i < cpus; i++)
			mvwprintw(padutil, 3 + i, 25, "%7.1f",
				  RAW(idle) / elapsed);
		    mvwprintw(padutil, 1, 25, "%7.1f",
			      RAWTOTAL(idle) / elapsed);
		    mvwprintw(padutil, 2, 32, "  Wait%%");
		    for (i = 0; i < cpus; i++)
			mvwprintw(padutil, 3 + i, 32, "%7.1f",
				  RAW(wait) / elapsed);
		    mvwprintw(padutil, 1, 32, "%7.1f",
			      RAWTOTAL(wait) / elapsed);

		    COLOUR wattrset(padutil, COLOR_PAIR(1));	/* Red */
		    mvwprintw(padutil, 2, 39, " HWirq%%");
		    for (i = 0; i < cpus; i++)
			mvwprintw(padutil, 3 + i, 39, "%7.1f",
				  RAW(irq) / elapsed);
		    mvwprintw(padutil, 1, 39, "%7.1f",
			      RAWTOTAL(irq) / elapsed);
		    mvwprintw(padutil, 2, 46, " SWirq%%");
		    for (i = 0; i < cpus; i++)
			mvwprintw(padutil, 3 + i, 46, "%7.1f",
				  RAW(softirq) / elapsed);
		    mvwprintw(padutil, 1, 46, "%7.1f",
			      RAWTOTAL(softirq) / elapsed);

		    COLOUR wattrset(padutil, COLOR_PAIR(5));	/* Magenta */
		    mvwprintw(padutil, 2, 53, " Steal%%");
		    for (i = 0; i < cpus; i++)
			mvwprintw(padutil, 3 + i, 53, "%7.1f",
				  RAW(steal) / elapsed);
		    mvwprintw(padutil, 1, 53, "%7.1f",
			      RAWTOTAL(steal) / elapsed);

		    COLOUR wattrset(padutil, COLOR_PAIR(6));	/* Cyan */
		    mvwprintw(padutil, 2, 60, " Guest%%");
		    for (i = 0; i < cpus; i++)
			mvwprintw(padutil, 3 + i, 60, "%7.1f",
				  RAW(guest) / elapsed);
		    mvwprintw(padutil, 1, 60, "%7.1f",
			      RAWTOTAL(guest) / elapsed);
		    mvwprintw(padutil, 2, 67, " GuestNice%%");
		    for (i = 0; i < cpus; i++)
			mvwprintw(padutil, 3 + i, 67, "%7.1f",
				  RAW(guest_nice) / elapsed);
		    mvwprintw(padutil, 1, 67, "%7.1f",
			      RAWTOTAL(guest_nice) / elapsed);
		}
		COLOUR wattrset(padutil, COLOR_PAIR(0));
		DISPLAY(padutil, i + 3);
	    } else {
		if (first_util) {
		    fprintf(fp,
			    "CPUUTIL_ALL,CPU Util Stats %s,User%%,Nice%%,Sys%%,Idle%%,Wait%%,Irq%%,Softirq%%,Steal%%,Guest%%,Guest_nice%%\n",
			    run_name);
		    for (i = 1; i <= cpus; i++)
			fprintf(fp,
				"CPUUTIL%03d,CPU Util Stats CPU%d %s,User%%,Nice%%,Sys%%,Idle%%,Wait%%,Irq%%,Softirq%%,Steal%%,Guest%%,Guest_nice%%\n",
				i, i, run_name);
		}
		fprintf(fp,
			"CPUUTIL_ALL,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
			LOOP, RAWTOTAL(user) / elapsed,
			RAWTOTAL(nice) / elapsed, RAWTOTAL(sys) / elapsed,
			RAWTOTAL(idle) / elapsed, RAWTOTAL(wait) / elapsed,
			RAWTOTAL(irq) / elapsed,
			RAWTOTAL(softirq) / elapsed,
			RAWTOTAL(steal) / elapsed,
			RAWTOTAL(guest) / elapsed,
			RAWTOTAL(guest_nice) / elapsed);
		for (i = 0; i < cpus; i++) {
		    fprintf(fp,
			    "CPUUTIL%03d,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
			    i, LOOP, RAW(user) / elapsed,
			    RAW(nice) / elapsed, RAW(sys) / elapsed,
			    RAW(idle) / elapsed, RAW(wait) / elapsed,
			    RAW(irq) / elapsed, RAW(softirq) / elapsed,
			    RAW(steal) / elapsed, RAW(guest) / elapsed,
			    RAW(guest_nice) / elapsed);
		}
	    }
	    first_util = 0;
	}
#ifdef POWER
	if (show_lpar) {
	    if (lparcfg.timebase == -1) {
		lparcfg.timebase = 0;
		proc_read(P_CPUINFO);
		for (i = 0; i < proc[P_CPUINFO].lines - 1; i++) {
		    if (!strncmp("timebase", proc[P_CPUINFO].line[i], 8)) {
			sscanf(proc[P_CPUINFO].line[i], "timebase : %lld",
			       &lparcfg.timebase);
			break;
		    }
		}
	    }
	    ret = proc_lparcfg();
	    if (cursed) {
		BANNER(padlpar, "PowerVM LPAR");
		if (ret == 0) {
		    COLOUR wattrset(padlpar, COLOR_PAIR(1));
		    mvwprintw(padlpar, 2, 0,
			      "Reading data from /proc/ppc64/lparcfg failed");
		    mvwprintw(padlpar, 3, 0,
			      "This is probably a Native Virtual Machine");
		    COLOUR wattrset(padlpar, COLOR_PAIR(0));
		} else
		    if (power_vm_type == VM_POWERKVM_HOST
			|| power_vm_type == VM_POWERKVM_GUEST) {
		    COLOUR wattrset(padlpar, COLOR_PAIR(5));
		    mvwprintw(padlpar, 2, 0,
			      "Reading data from /proc/ppc64/lparcfg mostly failed");
		    mvwprintw(padlpar, 3, 0,
			      "PowerKVM does not many of these stats");
		    COLOUR wattrset(padlpar, COLOR_PAIR(0));
		} else {
		    mvwprintw(padlpar, 1, 0,
			      "LPAR=%d  SerialNumber=%s  Type=%s",
			      lparcfg.partition_id, lparcfg.serial_number,
			      lparcfg.system_type);
		    mvwprintw(padlpar, 2, 0,
			      "Flags:      Shared-CPU=%-5s  Capped=%-5s   SMT-mode=%d",
			      lparcfg.
			      shared_processor_mode ? "true" : "false",
			      lparcfg.capped ? "true" : "false",
			      lparcfg.smt_mode);
		    COLOUR wattrset(padlpar, COLOR_PAIR(2));
		    mvwprintw(padlpar, 3, 0,
			      "Systems CPU Pool=%8.2f          Active=%8.2f    Total=%8.2f",
			      (float) lparcfg.pool_capacity / 100.0,
			      (float) lparcfg.system_active_processors,
			      (float) lparcfg.system_potential_processors);
		    COLOUR wattrset(padlpar, COLOR_PAIR(3));
		    mvwprintw(padlpar, 4, 0,
			      "LPARs CPU    Min=%8.2f     Entitlement=%8.2f      Max=%8.2f",
			      lparcfg.MinEntCap / 100.0,
			      lparcfg.partition_entitled_capacity / 100.0,
			      lparcfg.partition_max_entitled_capacity /
			      100.0);
		    COLOUR wattrset(padlpar, COLOR_PAIR(5));
		    mvwprintw(padlpar, 5, 0,
			      "Virtual CPU  Min=%8.2f          VP Now=%8.2f      Max=%8.2f",
			      (float) lparcfg.MinProcs,
			      (float) lparcfg.partition_active_processors,
			      (float) lparcfg.
			      partition_potential_processors);
		    COLOUR wattrset(padlpar, COLOR_PAIR(6));
		    mvwprintw(padlpar, 6, 0,
			      "Memory       Min=%8.2f         Desired=%8.2f  ",
			      (float) lparcfg.MinMem,
			      (float) lparcfg.DesMem);
		    COLOUR wattrset(padlpar, COLOR_PAIR(0));
		    mvwprintw(padlpar, 7, 0,
			      "Other     Weight=%8.2f   UnallocWeight=%8.2f Capacity=%8.2f",
			      (float) lparcfg.capacity_weight,
			      (float) lparcfg.unallocated_capacity_weight,
			      (float) lparcfg.CapInc / 100.0);

		    mvwprintw(padlpar, 8, 0,
			      "      BoundThrds=%8.2f UnallocCapacity=%8.2f  Increment",
			      (float) lparcfg.BoundThrds,
			      (float) lparcfg.unallocated_capacity);
		    if (lparcfg.purr_diff == 0 || lparcfg.timebase < 1) {
			mvwprintw(padlpar, 9, 0,
				  "lparcfg: purr field always zero, upgrade to SLES9+sp1 or RHEL4+u1");
		    } else {
			if (lpar_first_time) {
			    mvwprintw(padlpar, 9, 0,
				      "Please wait gathering data");

			    lpar_first_time = 0;
			} else {
			    COLOUR wattrset(padlpar, COLOR_PAIR(1));
			    mvwprintw(padlpar, 9, 0,
				      "Physical CPU use=%8.3f ",
				      (double) lparcfg.purr_diff /
				      (double) lparcfg.timebase / elapsed);
			    if (lparcfg.pool_idle_time != NUMBER_NOT_VALID
				&& lparcfg.pool_idle_saved != 0)
				mvwprintw(padlpar, 9, 29,
					  "PoolIdleTime=%8.2f",
					  (double) lparcfg.pool_idle_diff /
					  (double) lparcfg.timebase /
					  elapsed);
			    COLOUR wattrset(padlpar, COLOR_PAIR(0));
			    mvwprintw(padlpar, 9, 54, "[timebase=%lld]",
				      lparcfg.timebase);
			}
		    }
		}
		DISPLAY(padlpar, 10);
	    } else {
		/* Only print LPAR info to spreadsheet if in shared processor mode */
		if (ret != 0 && (lparcfg.shared_processor_mode > 0 || lparcfg.DedDonMode > 0)
		    && power_vm_type == VM_POWERVM)
		    fprintf(fp, "LPAR,%s,%9.6f,%d,%d,%d,%d,%d,%.2f,%.2f,%.2f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%.2f,%d\n", LOOP, (double) lparcfg.purr_diff / (double) lparcfg.timebase / elapsed, lparcfg.capped, lparcfg.shared_processor_mode, lparcfg.system_potential_processors, lparcfg.system_active_processors, lparcfg.pool_capacity /100, lparcfg.MinEntCap / 100.0, lparcfg.partition_entitled_capacity / 100.0, lparcfg.partition_max_entitled_capacity / 100.0, lparcfg.MinProcs, cpus,	/* report logical CPU here so analyser graph CPU% vs VPs reports correctly */
			    lparcfg.partition_active_processors,
			    lparcfg.partition_potential_processors,
			    lparcfg.capacity_weight,
			    lparcfg.unallocated_capacity_weight,
			    lparcfg.BoundThrds,
			    lparcfg.MinMem,
			    lparcfg.unallocated_capacity,
			    (double) lparcfg.pool_idle_diff /
			    (double) lparcfg.timebase / elapsed,
			    lparcfg.smt_mode);
	    }
	}
#endif	 /*POWER*/
#ifdef NVIDIA_GPU
	    if (show_gpu) {
	    if (!cursed && first_time_gpu)
		gpu_init();
	    for (i = 0; i < gpu_devices; i++) {
		if (cursed && first_time_gpu) {
		    if (nvmlDeviceGetName
			(gpu_device[i], &gpu_name[i][0],
			 1024) != NVML_SUCCESS)
			strcpy(gpu_name[i], "NVML API Failed");
		}
		if (nvmlDeviceGetUtilizationRates
		    (gpu_device[i], &gpu_util[i]) != NVML_SUCCESS) {
		    gpu_util[i].gpu = 999;
		    gpu_util[i].memory = 999;
		}
		if (nvmlDeviceGetTemperature
		    (gpu_device[i], NVML_TEMPERATURE_GPU,
		     &gpu_temp[i]) != NVML_SUCCESS)
		    gpu_temp[i] = 999;
		if (nvmlDeviceGetPowerUsage(gpu_device[i], &gpu_watts[i])
		    != NVML_SUCCESS)
		    gpu_watts[i] = 999000;
		if (nvmlDeviceGetClockInfo
		    (gpu_device[i], NVML_CLOCK_GRAPHICS,
		     &gpu_clock[i]) != NVML_SUCCESS)
		    gpu_clock[i] = 999;
	    }
	    if (cursed) {
		first_time_gpu = 0;
		BANNER(padgpu, "NVIDIA GPU Accelerator");

		mvwprintw(padgpu, 1, 1,
			  "Driver Version:%s    NVML Version: %s",
			  gpu_driver_version, gpu_nvml_version);

		mvwprintw(padgpu, 2, 1, "GPU");
		mvwprintw(padgpu, 3, 1, "No.");
		COLOUR wattrset(padgpu, COLOR_PAIR(1));
		mvwprintw(padgpu, 3, 5, "GPU-MHz");
		COLOUR wattrset(padgpu, COLOR_PAIR(2));
		mvwprintw(padgpu, 2, 14, "GPU-Utilisation");
		mvwprintw(padgpu, 3, 14, "Processor-Memory");
		COLOUR wattrset(padgpu, COLOR_PAIR(3));
		mvwprintw(padgpu, 2, 31, "Temperature");
		mvwprintw(padgpu, 3, 31, " Centigrade");
		COLOUR wattrset(padgpu, COLOR_PAIR(5));
		mvwprintw(padgpu, 2, 44, "Power-Use");
		mvwprintw(padgpu, 3, 44, "    Watts");
		COLOUR wattrset(padgpu, COLOR_PAIR(0));
		mvwprintw(padgpu, 2, 55, "Name");

		for (i = 0; i < gpu_devices; i++) {
		    mvwprintw(padgpu, 4 + i, 1, "%3d", i);
		    COLOUR wattrset(padgpu, COLOR_PAIR(1));
		    mvwprintw(padgpu, 4 + i, 5, "%7d", (int) gpu_clock[i]);
		    COLOUR wattrset(padgpu, COLOR_PAIR(2));
		    mvwprintw(padgpu, 4 + i, 14, "%7d%% %7d%%",
			      (int) gpu_util[i].gpu,
			      (int) gpu_util[i].memory);
		    COLOUR wattrset(padgpu, COLOR_PAIR(3));
		    mvwprintw(padgpu, 4 + i, 31, "%7d", (int) gpu_temp[i]);
		    COLOUR wattrset(padgpu, COLOR_PAIR(5));
		    mvwprintw(padgpu, 4 + i, 44, "%7.2f",
			      (int) gpu_watts[i] / 1000.0);
		    COLOUR wattrset(padgpu, COLOR_PAIR(0));
		    mvwprintw(padgpu, 4 + i, 55, "%-s", &gpu_name[i][0]);
		}
		DISPLAY(padgpu, 8);
	    } else {
		if (!show_rrd) {
		    if (first_time_gpu) {
			first_time_gpu = 0;
			fprintf(fp,
				"GPU_UTIL,NVidia GPU Utilisation Percent");
			for (i = 0; i < gpu_devices; i++)
			    fprintf(fp, ",GPU%d", i + 1);
			fprintf(fp, "\n");
			fprintf(fp,
				"GPU_MEM,NVidia Memory Utilisation Percent");
			for (i = 0; i < gpu_devices; i++)
			    fprintf(fp, ",GPU%d", i + 1);
			fprintf(fp, "\n");
			fprintf(fp, "GPU_TEMP,NVidia Temperature C");
			for (i = 0; i < gpu_devices; i++)
			    fprintf(fp, ",GPU%d", i + 1);
			fprintf(fp, "\n");
			fprintf(fp, "GPU_WATTS,NVidia Power Draw Watts");
			for (i = 0; i < gpu_devices; i++)
			    fprintf(fp, ",GPU%d", i + 1);
			fprintf(fp, "\n");
			fprintf(fp, "GPU_MHZ,NVidia GPU MHz");
			for (i = 0; i < gpu_devices; i++)
			    fprintf(fp, ",GPU%d", i + 1);
			fprintf(fp, "\n");
		    }
		    fprintf(fp, "GPU_UTIL,%s", LOOP);
		    for (i = 0; i < gpu_devices; i++)
			fprintf(fp, ",%d", (int) gpu_util[i].gpu);
		    fprintf(fp, "\n");
		    fprintf(fp, "GPU_MEM,%s", LOOP);
		    for (i = 0; i < gpu_devices; i++)
			fprintf(fp, ",%d", (int) gpu_util[i].memory);
		    fprintf(fp, "\n");
		    fprintf(fp, "GPU_TEMP,%s", LOOP);
		    for (i = 0; i < gpu_devices; i++)
			fprintf(fp, ",%d", (int) gpu_temp[i]);
		    fprintf(fp, "\n");
		    fprintf(fp, "GPU_WATTS,%s", LOOP);
		    for (i = 0; i < gpu_devices; i++)
			fprintf(fp, ",%d", (int) gpu_watts[i] / 1000);
		    fprintf(fp, "\n");
		    fprintf(fp, "GPU_MHZ,%s", LOOP);
		    for (i = 0; i < gpu_devices; i++)
			fprintf(fp, ",%d", (int) gpu_clock[i]);
		    fprintf(fp, "\n");
		}
	    }
	}
#endif				/*NVIDIA_GPU */
	if (show_mhz) {
	    int padline, lineno, cpuno, col, thrds, cores;
#ifdef POWER
	    char *clockstr = "clock  ";
#define DATACOL 9
#else
	    char *clockstr = "cpu MHz";
#define DATACOL 11
#endif				/* POWER */
	    proc_read(P_CPUINFO);

	    if (cursed) {
		/*
		   0123456789012345678
		   cpu MHz         : 3336.183    Intel
		   clock           : 3425.000000MHz Power
		 */
		lscpu_init();
#ifdef POWER
		if (lparcfg.smt_mode > lscpu.threads)
		    thrds = lparcfg.smt_mode;
		else
#endif		     /*POWER*/
			thrds = lscpu.threads;
		if (thrds < 1)
		    thrds = 1;
		BANNER(padmhz, "CPU MHz per Core and Thread");
#ifdef POWER
		mvwprintw(padmhz, 1, 10,
			  "lparcfgSMT=%d lscpu.threads=%d  mode=%d  [1=AllCPUs 2=Cores 3=Graphs]",
			  lparcfg.smt_mode, lscpu.threads, show_mhz);
#else				/*POWER */
		mvwprintw(padmhz, 1, 10,
			  "lscpu.threads=%d  mode=%d  [1=AllCPUs 2=Cores 3=Graphs]",
			  lscpu.threads, show_mhz);
#endif				/*POWER */
		if (show_mhz == 1)
		    mvwprintw(padmhz, 2, 1, "CPU MHz  ");
		else
		    mvwprintw(padmhz, 2, 1, "Core MHz ");
		if (show_mhz == 3)
		    mvwprintw(padmhz, 2, 10,
			      "---------1---------2---------3---------4---------5---------6 GHz");

		col = 0;
		cpuno = 1;
		cores = 0;
		padline = 3;
		min_mhz = 999999999999999999.0;
		max_mhz = 0.0;
		for (lineno = 0; lineno < proc[P_CPUINFO].lines; lineno++) {
		    if (strncmp
			(clockstr, proc[P_CPUINFO].line[lineno],
			 strlen(clockstr)) == 0) {
			if (show_mhz == 1
			    || ((show_mhz == 2 || show_mhz == 3)
				&& ((cpuno + 7) % thrds) == 0)) {
			    cores++;
			    mhz = 0.0;
			    sscanf(&proc[P_CPUINFO].line[lineno][DATACOL],
				   "%f", &mhz);
			    mvwprintw(padmhz, padline, col, "%3d=%4.0f",
				      (show_mhz != 1) ? cores : cpuno, mhz);
			    if (show_mhz == 3) {
				if (mhz > avg_mhz) {
				    COLOUR wattrset(padmhz, COLOR_PAIR(1));
				} else {
				    COLOUR wattrset(padmhz, COLOR_PAIR(2));
				}
				for (i = 1; i < mhz / 100; i++)
				    mvwprintw(padmhz, padline, col + 9 + i, "#");
				COLOUR wattrset(padmhz, COLOR_PAIR(0));
				for (; i < 60; i++)
				    mvwprintw(padmhz, padline, col + 9 + i, " ");
			    }
			    padline++;
			    if (padline > 22) {
				padline = 3;
				col = col + 9;
			    }
			    if (mhz != 0.0) {
				if (mhz < min_mhz)
				    min_mhz = mhz;
				if (mhz > max_mhz)
				    max_mhz = mhz;
			    }
			}
			cpuno++;
		    }
		    if (cpuno > 160)
			break;
		}
		avg_mhz = (min_mhz + max_mhz) / 2;
		if(cores >= 20)
			lineno = 23;
		else
			lineno = cores+3;
		DISPLAY(padmhz, lineno);
	    } else {
		if (!show_rrd)
		    fprintf(fp, "MHZ,%s", LOOP);
		for (lineno = 0; lineno < proc[P_CPUINFO].lines; lineno++) {
		    if (strncmp
			(clockstr, proc[P_CPUINFO].line[lineno],
			 strlen(clockstr)) == 0) {
			mhz = 0.0;
			sscanf(&proc[P_CPUINFO].line[lineno][DATACOL],
			       "%f", &mhz);
			if (!show_rrd)
			    fprintf(fp, ",%.0f", mhz);
		    }
		}
		if (!show_rrd)
		    fprintf(fp, "\n");
	    }
	}
	if (show_memory) {
	    proc_read(P_MEMINFO);
	    proc_mem();
	    if (cursed) {
#define RAMCOL 16
#define SWAPCOL 28
#define HIGHCOL 45
#define LOWCOL 60

		BANNER(padmem, "Memory and Swap");

		COLOUR wattrset(padmem, COLOR_PAIR(1));
		mvwprintw(padmem, 1, 1, "PageSize:%dKB", pagesize / 1024);
		COLOUR wattrset(padmem, COLOR_PAIR(0));
		mvwprintw(padmem, 2, 1, "Total (MB)");
		mvwprintw(padmem, 3, 1, "Free  (MB)");
		mvwprintw(padmem, 4, 1, "Free Percent");

		COLOUR wattrset(padmem, COLOR_PAIR(2));
		mvwprintw(padmem, 1, RAMCOL, "RAM-Memory");
		mvwprintw(padmem, 2, RAMCOL, "%10.1f",
			  p->mem.memtotal / 1024.0);
		mvwprintw(padmem, 3, RAMCOL, "%10.1f",
			  p->mem.memfree / 1024.0);
		mvwprintw(padmem, 4, RAMCOL, "%10.1f%%",
			  p->mem.memfree ==
			  0 ? 0.0 : 100.0 * (float) p->mem.memfree /
			  (float) p->mem.memtotal);
		COLOUR wattrset(padmem, COLOR_PAIR(3));
		mvwprintw(padmem, 1, SWAPCOL, "Swap-Space");
		mvwprintw(padmem, 2, SWAPCOL, "%10.1f",
			  p->mem.swaptotal / 1024.0);
		mvwprintw(padmem, 3, SWAPCOL, "%10.1f",
			  p->mem.swapfree / 1024.0);
		mvwprintw(padmem, 4, SWAPCOL, "%10.1f%%",
			  p->mem.swapfree ==
			  0 ? 0.0 : 100.0 * (float) p->mem.swapfree /
			  (float) p->mem.swaptotal);
		COLOUR wattrset(padmem, COLOR_PAIR(4));
		mvwprintw(padmem, 1, HIGHCOL, "High-Memory");
		if (p->mem.hightotal > 0.0) {
		    mvwprintw(padmem, 2, HIGHCOL, "%8.1f",
			      p->mem.hightotal / 1024.0);
		    mvwprintw(padmem, 3, HIGHCOL, "%8.1f",
			      p->mem.highfree / 1024.0);
		    mvwprintw(padmem, 4, HIGHCOL, "%8.1f%%",
			      p->mem.highfree ==
			      0 ? 0.0 : 100.0 * (float) p->mem.highfree /
			      (float) p->mem.hightotal);
		} else
		    mvwprintw(padmem, 2, HIGHCOL, "- not in use");
		COLOUR wattrset(padmem, COLOR_PAIR(6));
		mvwprintw(padmem, 1, LOWCOL, " Low-Memory");
		if (p->mem.lowtotal > 0.0) {
		    mvwprintw(padmem, 2, LOWCOL, "%8.1f",
			      p->mem.lowtotal / 1024.0);
		    mvwprintw(padmem, 3, LOWCOL, "%8.1f",
			      p->mem.lowfree / 1024.0);
		    mvwprintw(padmem, 4, LOWCOL, "%8.1f%%",
			      p->mem.lowfree ==
			      0 ? 0.0 : 100.0 * (float) p->mem.lowfree /
			      (float) p->mem.lowtotal);
		} else
		    mvwprintw(padmem, 2, LOWCOL, "- not in use");
		COLOUR wattrset(padmem, COLOR_PAIR(5));


		mvwprintw(padmem, 5, 1,
			  "Linux Kernel Internal Memory (MB)");
#ifndef SMALLMEM
		mvwprintw(padmem, 6, 1,
			  "                       Cached=%10.1f     Active=%10.1f",
			  p->mem.cached / 1024.0, p->mem.active / 1024.0);
#else
		mvwprintw(padmem, 6, 1,
			  " Shared=%10.1f     Cached=%10.1f     Active=%10.1f",
			  p->mem.memshared / 1024.0,
			  p->mem.cached / 1024.0, p->mem.active / 1024.0);
		mvwprintw(padmem, 5, 68, "MB");
		mvwprintw(padmem, 6, 55, "bigfree=%10.1f",
			  p->mem.bigfree / 1024);
#endif		 /*SMALLMEM*/
		    mvwprintw(padmem, 7, 1,
			      "Buffers=%10.1f Swapcached=%10.1f  Inactive =%10.1f",
			      p->mem.buffers / 1024.0,
			      p->mem.swapcached / 1024.0,
			      p->mem.inactive / 1024.0);
#ifndef SMALLMEM
		mvwprintw(padmem, 8, 1,
			  "Dirty  =%10.1f Writeback =%10.1f  Mapped   =%10.1f",
			  p->mem.dirty / 1024.0, p->mem.writeback / 1024.0,
			  p->mem.mapped / 1024.0);
		mvwprintw(padmem, 9, 1,
			  "Slab   =%10.1f Commit_AS =%10.1f PageTables=%10.1f",
			  p->mem.slab / 1024.0,
			  p->mem.committed_as / 1024.0,
			  p->mem.pagetables / 1024.0);
#endif /*SMALLMEM */
#ifdef POWER
		if (!show_lpar)	/* check if already called above */
		    proc_lparcfg();
		if (lparcfg.cmo_enabled == 0)
		    mvwprintw(padmem, 10, 1, "AMS is not active");
		else
		    mvwprintw(padmem, 10, 1,
			      "AMS id=%d Weight=%-3d pmem=%ldMB hpi=%.1f/s hpit=%.1f(sec) Pool=%ldMB Loan=%ldKB     ",
			      (int) lparcfg.entitled_memory_pool_number,
			      (int) lparcfg.entitled_memory_weight,
			      (long) (lparcfg.backing_memory) / 1024 /
			      1024,
			      (double) (lparcfg.cmo_faults_diff) / elapsed,
			      (double) (lparcfg.cmo_fault_time_usec_diff) /
			      1000 / 1000 / elapsed,
			      (long) lparcfg.entitled_memory_pool_size /
			      1024 / 1024,
			      (long) lparcfg.entitled_memory_loan_request /
			      1024);

		COLOUR wattrset(padmem, COLOR_PAIR(0));
		DISPLAY(padmem, 11);
#else				/* POWER */
		COLOUR wattrset(padmem, COLOR_PAIR(0));
		DISPLAY(padmem, 10);
#endif				/* POWER */
	    } else {

		if (show_rrd)
		    str_p =
			"rrdtool update mem.rrd %s:%.1f:%.1f:%.1f:%.1f:%.1f:%.1f:%.1f:%.1f:%.1f:%.1f:%.1f:%.1f:%.1f:%.1f:%.1f\n";
		else
		    str_p =
			"MEM,%s,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n";
		fprintf(fp, str_p, LOOP, p->mem.memtotal / 1024.0,
			p->mem.hightotal / 1024.0,
			p->mem.lowtotal / 1024.0,
			p->mem.swaptotal / 1024.0, p->mem.memfree / 1024.0,
			p->mem.highfree / 1024.0, p->mem.lowfree / 1024.0,
			p->mem.swapfree / 1024.0,
			p->mem.memshared / 1024.0, p->mem.cached / 1024.0,
			p->mem.active / 1024.0,
#ifndef SMALLMEM
			-1.0,
#else
			p->mem.bigfree / 1024.0,
#endif			 /*SMALLMEM*/
			p->mem.buffers / 1024.0,
			p->mem.swapcached / 1024.0,
			p->mem.inactive / 1024.0);
#ifdef POWER
		if (lparcfg.cmo_enabled != 0) {
		    if (!show_rrd)
			fprintf(fp,
				"MEMAMS,%s,%d,%d,%.1f,%.3lf,0,0,0,%.1f,%ld,%ld,%ld\n",
				LOOP,
				(int) lparcfg.entitled_memory_pool_number,
				(int) lparcfg.entitled_memory_weight,
				(float) (lparcfg.cmo_faults_diff) /
				elapsed,
				(float) (lparcfg.
					 cmo_fault_time_usec_diff) / 1000 /
				1000 / elapsed,
				/* three zeros here */
				(float) (lparcfg.backing_memory) / 1024 /
				1024, lparcfg.cmo_page_size / 1024,
				lparcfg.entitled_memory_pool_size / 1024 /
				1024,
				lparcfg.entitled_memory_loan_request /
				1024);
		}
#ifdef EXPERIMENTAL
		if (!show_rrd)
		    fprintf(fp,
			    "MEMEXPERIMENTAL,%s,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld\n",
			    LOOP, (long) lparcfg.DesEntCap,
			    (long) lparcfg.DesProcs,
			    (long) lparcfg.DesVarCapWt,
			    (long) lparcfg.DedDonMode,
			    (long) lparcfg.group, (long) lparcfg.pool,
			    (long) lparcfg.entitled_memory,
			    (long) lparcfg.entitled_memory_group_number,
			    (long) lparcfg.
			    unallocated_entitled_memory_weight,
			    (long) lparcfg.
			    unallocated_io_mapping_entitlement);
#endif				/* EXPERIMENTAL */
#endif				/* POWER */
	    }
/* for testing large page		
		p->mem.hugefree = 250;
		p->mem.hugetotal = 1000;
		p->mem.hugesize = 16*1024;
*/
	}
#ifndef SMALLMEM
	if (show_large) {
	    proc_read(P_MEMINFO);
	    proc_mem();
	    if (cursed) {
		BANNER(padlarge, "Large (Huge) Page");
		if (p->mem.hugetotal > 0) {
		    if (p->mem.hugetotal - p->mem.hugefree > huge_peak)
			huge_peak = p->mem.hugetotal - p->mem.hugefree;
		    mvwprintw(padlarge, 1, 1,
			      "Total Pages=%7ld   100.0%%   Huge Page Size =%ld KB",
			      p->mem.hugetotal, p->mem.hugesize);
		    mvwprintw(padlarge, 2, 1,
			      "Used  Pages=%7ld   %5.1f%%   Used Pages Peak=%-8ld",
			      (long) (p->mem.hugetotal - p->mem.hugefree),
			      (p->mem.hugetotal -
			       p->mem.hugefree) /
			      (float) p->mem.hugetotal * 100.0, huge_peak);
		    mvwprintw(padlarge, 3, 1, "Free  Pages=%7ld   %5.1f%%",
			      p->mem.hugefree,
			      p->mem.hugefree / (float) p->mem.hugetotal *
			      100.0);
		} else {
		    mvwprintw(padlarge, 1, 1, " There are no Huge Pages");
		    mvwprintw(padlarge, 2, 1, " - see /proc/meminfo");
		}
		DISPLAY(padlarge, 4);
	    } else {
		if (p->mem.hugetotal > 0) {
		    if (first_huge == 1) {
			first_huge = 0;
			fprintf(fp,
				"HUGEPAGES,Huge Page Use %s,HugeTotal,HugeFree,HugeSizeMB\n",
				run_name);
		    }
		    fprintf(fp, "HUGEPAGES,%s,%ld,%ld,%.1f\n",
			    LOOP,
			    p->mem.hugetotal,
			    p->mem.hugefree, p->mem.hugesize / 1024.0);
		}
	    }
	}
#endif /* SMALLMEM */
	if (show_vm) {
#define VMDELTA(variable) (p->vm.variable - q->vm.variable)
#define VMCOUNT(variable) (p->vm.variable                 )
	    ret = read_vmstat();
	    if (cursed) {
		BANNER(padpage, "Virtual Memory");

		COLOUR wattrset(padpage, COLOR_PAIR(6));
		if (ret < 0) {
		    mvwprintw(padpage, 2, 2,
			      "Virtual Memory stats not supported with this kernel");
		    mvwprintw(padpage, 3, 2,
			      "/proc/vmstat only seems to appear in 2.6 onwards");

		} else {
		    if (vm_first_time) {
			mvwprintw(padpage, 2, 2,
				  "Please wait - collecting data");
			vm_first_time = 0;
		    } else {
			mvwprintw(padpage, 1, 0,
				  "nr_dirty    =%9lld pgpgin      =%8lld",
				  VMCOUNT(nr_dirty), VMDELTA(pgpgin));
			mvwprintw(padpage, 2, 0,
				  "nr_writeback=%9lld pgpgout     =%8lld",
				  VMCOUNT(nr_writeback), VMDELTA(pgpgout));
			mvwprintw(padpage, 3, 0,
				  "nr_unstable =%9lld pgpswpin    =%8lld",
				  VMCOUNT(nr_unstable), VMDELTA(pswpin));
			mvwprintw(padpage, 4, 0,
				  "nr_table_pgs=%9lld pgpswpout   =%8lld",
				  VMCOUNT(nr_page_table_pages),
				  VMDELTA(pswpout));
			mvwprintw(padpage, 5, 0,
				  "nr_mapped   =%9lld pgfree      =%8lld",
				  VMCOUNT(nr_mapped), VMDELTA(pgfree));
			if(VMCOUNT(nr_slab) != -1 ) { /* older nr_slab only */
			    mvwprintw(padpage, 6, 0,
				  "nr_slab     =%9lld pgactivate  =%8lld",
				  VMCOUNT(nr_slab), VMDELTA(pgactivate));
			    mvwprintw(padpage, 7, 0,
				  "                       pgdeactivate=%8lld",
				  VMDELTA(pgdeactivate));
			} else { /*new nr_slab_reclaimable / nr_slab_unreclaimable Kernel 2.6.19+ */
			    mvwprintw(padpage, 6, 0,
				  "slab_reclaim=%9lld pgactivate  =%8lld",
				  VMCOUNT(nr_slab_reclaimable), VMDELTA(pgactivate));
			    mvwprintw(padpage, 7, 0,
				  "slab_unreclm=%9lld pgdeactivate=%8lld",
				  VMCOUNT(nr_slab_unreclaimable), VMDELTA(pgdeactivate));
			}
			mvwprintw(padpage, 8, 0,
				  "allocstall  =%9lld pgfault     =%8lld  kswapd_steal     =%7lld",
				  VMDELTA(allocstall), VMDELTA(pgfault),
				  VMDELTA(kswapd_steal));
			mvwprintw(padpage, 9, 0,
				  "pageoutrun  =%9lld pgmajfault  =%8lld  kswapd_inodesteal=%7lld",
				  VMDELTA(pageoutrun), VMDELTA(pgmajfault),
				  VMDELTA(kswapd_inodesteal));
			mvwprintw(padpage, 10, 0,
				  "slabs_scanned=%8lld pgrotated   =%8lld  pginodesteal     =%7lld",
				  VMDELTA(slabs_scanned),
				  VMDELTA(pgrotated),
				  VMDELTA(pginodesteal));



			mvwprintw(padpage, 1, 46,
				  "              High Normal    DMA");
			mvwprintw(padpage, 2, 46,
				  "alloc      %7lld%7lld%7lld",
				  VMDELTA(pgalloc_high),
				  VMDELTA(pgalloc_normal),
				  VMDELTA(pgalloc_dma));
			mvwprintw(padpage, 3, 46,
				  "refill     %7lld%7lld%7lld",
				  VMDELTA(pgrefill_high),
				  VMDELTA(pgrefill_normal),
				  VMDELTA(pgrefill_dma));
			mvwprintw(padpage, 4, 46,
				  "steal      %7lld%7lld%7lld",
				  VMDELTA(pgsteal_high),
				  VMDELTA(pgsteal_normal),
				  VMDELTA(pgsteal_dma));
			mvwprintw(padpage, 5, 46,
				  "scan_kswapd%7lld%7lld%7lld",
				  VMDELTA(pgscan_kswapd_high),
				  VMDELTA(pgscan_kswapd_normal),
				  VMDELTA(pgscan_kswapd_dma));
			mvwprintw(padpage, 6, 46,
				  "scan_direct%7lld%7lld%7lld",
				  VMDELTA(pgscan_direct_high),
				  VMDELTA(pgscan_direct_normal),
				  VMDELTA(pgscan_direct_dma));
		    }
		}
		COLOUR wattrset(padpage, COLOR_PAIR(0));
		DISPLAY(padpage, 11);
	    } else {
		if (ret < 0) {
		    show_vm = 0;
		} else if (vm_first_time) {
		    vm_first_time = 0;
		    if(VMCOUNT(nr_slab) == -1 ) 
			    slabstr = "nr_slab_reclaimable";
		    else
			    slabstr = "nr_slab";
		    fprintf(fp,
			    "VM,Paging and Virtual Memory,nr_dirty,nr_writeback,nr_unstable,nr_page_table_pages,nr_mapped,%s,pgpgin,pgpgout,pswpin,pswpout,pgfree,pgactivate,pgdeactivate,pgfault,pgmajfault,pginodesteal,slabs_scanned,kswapd_steal,kswapd_inodesteal,pageoutrun,allocstall,pgrotated,pgalloc_high,pgalloc_normal,pgalloc_dma,pgrefill_high,pgrefill_normal,pgrefill_dma,pgsteal_high,pgsteal_normal,pgsteal_dma,pgscan_kswapd_high,pgscan_kswapd_normal,pgscan_kswapd_dma,pgscan_direct_high,pgscan_direct_normal,pgscan_direct_dma\n", slabstr);
		}
		if (show_rrd)
		    str_p = "rrdtool update vm.rrd %s"
			":%lld:%lld:%lld:%lld:%lld"
			":%lld:%lld:%lld:%lld:%lld"
			":%lld:%lld:%lld:%lld:%lld"
			":%lld:%lld:%lld:%lld:%lld"
			":%lld:%lld:%lld:%lld:%lld"
			":%lld:%lld:%lld:%lld:%lld"
			":%lld:%lld:%lld:%lld:%lld" ":%lld:%lld\n";
		else
		    str_p = "VM,%s"
			",%lld,%lld,%lld,%lld,%lld"
			",%lld,%lld,%lld,%lld,%lld"
			",%lld,%lld,%lld,%lld,%lld"
			",%lld,%lld,%lld,%lld,%lld"
			",%lld,%lld,%lld,%lld,%lld"
			",%lld,%lld,%lld,%lld,%lld"
			",%lld,%lld,%lld,%lld,%lld" ",%lld,%lld\n";
		if(VMCOUNT(nr_slab) != -1)
			tmpslab = VMCOUNT(nr_slab);
		else
			tmpslab = VMCOUNT(nr_slab_reclaimable);
		fprintf(fp, str_p,
			LOOP,
			VMCOUNT(nr_dirty),
			VMCOUNT(nr_writeback),
			VMCOUNT(nr_unstable),
			VMCOUNT(nr_page_table_pages),
			VMCOUNT(nr_mapped),
			tmpslab,
			VMDELTA(pgpgin),
			VMDELTA(pgpgout),
			VMDELTA(pswpin),
			VMDELTA(pswpout),
			VMDELTA(pgfree),
			VMDELTA(pgactivate),
			VMDELTA(pgdeactivate),
			VMDELTA(pgfault),
			VMDELTA(pgmajfault),
			VMDELTA(pginodesteal),
			VMDELTA(slabs_scanned),
			VMDELTA(kswapd_steal),
			VMDELTA(kswapd_inodesteal),
			VMDELTA(pageoutrun),
			VMDELTA(allocstall),
			VMDELTA(pgrotated),
			VMDELTA(pgalloc_high),
			VMDELTA(pgalloc_normal),
			VMDELTA(pgalloc_dma),
			VMDELTA(pgrefill_high),
			VMDELTA(pgrefill_normal),
			VMDELTA(pgrefill_dma),
			VMDELTA(pgsteal_high),
			VMDELTA(pgsteal_normal),
			VMDELTA(pgsteal_dma),
			VMDELTA(pgscan_kswapd_high),
			VMDELTA(pgscan_kswapd_normal),
			VMDELTA(pgscan_kswapd_dma),
			VMDELTA(pgscan_direct_high),
			VMDELTA(pgscan_direct_normal),
			VMDELTA(pgscan_direct_dma));
	    }
	}
	if (show_kernel) {
	    proc_read(P_STAT);
	    proc_cpu();
	    proc_read(P_UPTIME);
	    proc_read(P_LOADAVG);
	    proc_kernel();
	    if (cursed) {
		BANNER(padker, "Kernel and Load Average");
#define MORECOL 21
#define LOADCOL 41
#define BOOTCOL 55
		COLOUR wattrset(padker, COLOR_PAIR(1));
		mvwprintw(padker, 1, 0, "Global-CPU-Stats---->");
		mvwprintw(padker, 2, 0, " /proc/stat line 1");
		mvwprintw(padker, 3, 0, "%ld ticks per second", ticks);
		mvwprintw(padker, 4, 0, "100%%=1 CPUcoreThread");
		COLOUR wattrset(padker, COLOR_PAIR(2));
		mvwprintw(padker, 5, 0, "%8lld   RunQueue",
			  p->cpu_total.running);
		mvwprintw(padker, 6, 0, "%8lld   Blocked",
			  p->cpu_total.blocked);
		mvwprintw(padker, 7, 0, "%10.1f Context",
			  (float) (p->cpu_total.ctxt -
				   q->cpu_total.ctxt) / elapsed);
		mvwprintw(padker, 8, 0, "           Switch");
		mvwprintw(padker, 9, 0, "%10.1f Forks",
			  (float) (p->cpu_total.procs -
				   q->cpu_total.procs) / elapsed);
		mvwprintw(padker, 10, 0, "%10.1f Interrupts",
			  (float) (p->cpu_total.intr -
				   q->cpu_total.intr) / elapsed);

		COLOUR wattrset(padker, COLOR_PAIR(1));
		mvwprintw(padker, 1, MORECOL, "%8.1f%% user",
			  (float) (RAWTOTAL(user)) / elapsed);
		mvwprintw(padker, 2, MORECOL, "%8.1f%% user_nice",
			  (float) (RAWTOTAL(nice)) / elapsed);
		mvwprintw(padker, 3, MORECOL, "%8.1f%% system",
			  (float) (RAWTOTAL(sys)) / elapsed);
		mvwprintw(padker, 4, MORECOL, "%8.1f%% idle",
			  (float) (RAWTOTAL(idle)) / elapsed);
		mvwprintw(padker, 5, MORECOL, "%8.1f%% iowait",
			  (float) (RAWTOTAL(wait)) / elapsed);
		mvwprintw(padker, 6, MORECOL, "%8.1f%% irq",
			  (float) (RAWTOTAL(irq)) / elapsed);
		mvwprintw(padker, 7, MORECOL, "%8.1f%% softirq",
			  (float) (RAWTOTAL(softirq)) / elapsed);
		mvwprintw(padker, 8, MORECOL, "%8.1f%% steal",
			  (float) (RAWTOTAL(steal)) / elapsed);
		mvwprintw(padker, 9, MORECOL, "%8.1f%% guest",
			  (float) (RAWTOTAL(guest)) / elapsed);
		mvwprintw(padker, 10, MORECOL, "%8.1f%% guest_nice",
			  (float) (RAWTOTAL(guest_nice)) / elapsed);

		COLOUR wattrset(padker, COLOR_PAIR(3));
		mvwprintw(padker, 1, LOADCOL, "Load Average");
		mvwprintw(padker, 2, LOADCOL, " 1 mins %5.2f",
			  (float) p->cpu_total.mins1);
		mvwprintw(padker, 3, LOADCOL, " 5 mins %5.2f",
			  (float) p->cpu_total.mins5);
		mvwprintw(padker, 4, LOADCOL, "15 mins %5.2f",
			  (float) p->cpu_total.mins15);


		COLOUR wattrset(padker, COLOR_PAIR(5));
		mvwprintw(padker, 1, BOOTCOL, "CPU use since boottime");

		updays = p->cpu_total.uptime / 60 / 60 / 24;
		uphours =
		    (p->cpu_total.uptime -
		     updays * 60 * 60 * 24) / 60 / 60;
		upmins =
		    (p->cpu_total.uptime - updays * 60 * 60 * 24 -
		     uphours * 60 * 60) / 60;
		mvwprintw(padker, 2, BOOTCOL, "Uptime Days Hours Mins");
		mvwprintw(padker, 3, BOOTCOL, "Uptime %4ld %5ld %4ld",
			  updays, uphours, upmins);

		updays = p->cpu_total.idletime / 60 / 60 / 24 / cpus;
		uphours =
		    (p->cpu_total.idletime -
		     updays * 60 * 60 * 24) / 60 / 60 / cpus;
		upmins =
		    (p->cpu_total.idletime - updays * 60 * 60 * 24 -
		     uphours * 60 * 60) / 60 / cpus;
		mvwprintw(padker, 4, BOOTCOL, "Idle   %4ld %5ld %4ld",
			  updays, uphours, upmins);

		average =
		    (p->cpu_total.uptime -
		     p->cpu_total.idletime) / p->cpu_total.uptime * 100.0;
		if (average > 0.0)
		    mvwprintw(padker, 5, BOOTCOL,
			      "Average Busy Uptimee=%6.2f%%", average);
		else
		    mvwprintw(padker, 5, BOOTCOL, "Uptime has overflowed");
		mvwprintw(padker, 7, BOOTCOL, "%d CPU core threads", cpus);
		mvwprintw(padker, 9, BOOTCOL, "Boot time %d", boottime);
		mvwprintw(padker,10, BOOTCOL, "%s", boottime_str);
		COLOUR wattrset(padker, COLOR_PAIR(0));
		DISPLAY(padker, 11);
	    } else {
		if (proc_first_time) {
		    q->cpu_total.ctxt = p->cpu_total.ctxt;
		    q->cpu_total.procs = p->cpu_total.procs;
		    proc_first_time = 0;
		}
		if (show_rrd)
		    str_p =                    /*   LOOP    1    2    3    4    5    6    7    8    9 */
			"rrdtool update proc.rrd %s:%.0f:%.0f:%.1f:%.1f:%.1f:%.1f:%.1f:%.1f:%.1f:%.1f\n";
		else
		    str_p = /*   LOOP    1    2    3    4    5    6    7    8    9 */
			"PROC,%s,%.0f,%.0f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n";

		/* These "-1"'s looks bad but it keeps the nmon for AIX format */
		/* The stats are not available in Linux . . .  unless you know better! */
		fprintf(fp, str_p, LOOP, 
			(float) p->cpu_total.running,	/*1 runqueue */
			(float) p->cpu_total.blocked,	/*2 swapin (# of processes waiting for IO completion */
			(float) (p->cpu_total.ctxt - q->cpu_total.ctxt) / elapsed, /*3 pswitch */
			-1.0,	/*4 syscall */
			-1.0,	/*4 read */
			-1.0,	/*5 write */
			(float) (p->cpu_total.procs - q->cpu_total.procs) / elapsed, /*6 fork */
			-1.0,	/*7 exec */
			-1.0,	/*8 sem */
			-1.0);	/*9 msg */
	    }
	}

	if (show_nfs) {
	    proc_read(P_NFS);
	    proc_read(P_NFSD);
	    proc_nfs();

	    if (cursed) {
		if (nfs_first_time) {
		    memcpy(&q->nfs, &p->nfs, sizeof(struct nfs_stat));
		    nfs_first_time = 0;
		}
		if (nfs_clear) {
		    nfs_clear = 0;
		    for (i = 0; i < 25; i++)
			mvwprintw(padnfs, i, 0,
				  "                                                                                ");
		}
		BANNER(padnfs,
		       "Network Filesystem (NFS) I/O Operations per second");
		if (show_nfs == 1) {
		    if (nfs_v2c_found || nfs_v2s_found)
			mvwprintw(padnfs, 1, 0,
				  " Version 2        Client   Server");
		    else
			mvwprintw(padnfs, 1, 0, " Version 2 not active");

		    if (nfs_v3c_found || nfs_v3s_found)
			mvwprintw(padnfs, 1, 41,
				  "Version 3      Client   Server");
		    else
			mvwprintw(padnfs, 1, 41, " Version 3 not active");
		}
		if (show_nfs == 2) {
		    if (nfs_v4c_found)
			mvwprintw(padnfs, 1, 0,
				  " Version 4 Client (%d Stats found)",
				  nfs_v4c_names_count);
		    else
			mvwprintw(padnfs, 1, 0,
				  " Version 4 Client side not active");
		}
		if (show_nfs == 3) {
		    if (nfs_v4s_found)
			mvwprintw(padnfs, 1, 0,
				  " Version 4 Server (%d Stats found)",
				  nfs_v4s_names_count);
		    else
			mvwprintw(padnfs, 1, 0,
				  " Version 4 Server side not active");
		}
#define NFS_TOTAL(member) (double)(p->member)
#define NFS_DELTA(member) (((double)(p->member - q->member)/elapsed))
		v2c_total = 0;
		v2s_total = 0;
		v3c_total = 0;
		v3s_total = 0;
		v4c_total = 0;
		v4s_total = 0;
		if (nfs_v3c_found || nfs_v3s_found) {
		    for (i = 0; i < 18; i++) {	/* NFS V2 Client & Server */
			if (show_nfs == 1)
			    mvwprintw(padnfs, 2 + i, 3, "%12s %8.1f %8.1f",
				      nfs_v2_names[i],
				      NFS_DELTA(nfs.v2c[i]),
				      NFS_DELTA(nfs.v2s[i]));
			v2c_total += NFS_DELTA(nfs.v2c[i]);
			v2s_total += NFS_DELTA(nfs.v2s[i]);
		    }
		}
		if (nfs_v3c_found || nfs_v3s_found) {
		    for (i = 0; i < 22; i++) {	/* NFS V3 Client & Server */
			if (show_nfs == 1)
			    mvwprintw(padnfs, 2 + i, 41,
				      "%12s %8.1f %8.1f", nfs_v3_names[i],
				      NFS_DELTA(nfs.v3c[i]),
				      NFS_DELTA(nfs.v3s[i]));
			v3c_total += NFS_DELTA(nfs.v3c[i]);
			v3s_total += NFS_DELTA(nfs.v3s[i]);
		    }
		}

		if (nfs_v4c_found) {
		    for (i = 0; i < 18; i++) {	/* NFS V4 Client */
			if (show_nfs == 2) {
			    mvwprintw(padnfs, 2 + i, 0, "%12s%7.1f",
				      nfs_v4c_names[i],
				      NFS_DELTA(nfs.v4c[i]));
			}
			v4c_total += NFS_DELTA(nfs.v4c[i]);
		    }
		    for (i = 18; i < 35; i++) {	/* NFS V4 Client */
			if (show_nfs == 2) {
			    mvwprintw(padnfs, 2 + i - 18, 20, "%12s%7.1f",
				      nfs_v4c_names[i],
				      NFS_DELTA(nfs.v4c[i]));
			}
			v4c_total += NFS_DELTA(nfs.v4c[i]);
		    }
		}

		if (nfs_v4s_found) {
		    for (i = 0; i < 18; i++) {	/* NFS V4 Server */
			if (show_nfs == 3) {
			    mvwprintw(padnfs, 2 + i, 0, "%12s%7.1f",
				      nfs_v4s_names[i],
				      NFS_DELTA(nfs.v4s[i]));
			}
			v4s_total += NFS_DELTA(nfs.v4s[i]);
		    }
		    for (i = 18; i < 36; i++) {	/* NFS V4 Server */
			if (show_nfs == 3) {
			    mvwprintw(padnfs, 2 + i - 18, 19, "%12s%7.1f",
				      nfs_v4s_names[i],
				      NFS_DELTA(nfs.v4s[i]));
			}
			v4s_total += NFS_DELTA(nfs.v4s[i]);
		    }
		    for (i = 36; i < 54 && i < nfs_v4s_names_count; i++) {	/* NFS V4 Server */
			if (show_nfs == 3) {
			    mvwprintw(padnfs, 2 + i - 36, 39, "%12s%7.1f",
				      nfs_v4s_names[i],
				      NFS_DELTA(nfs.v4s[i]));
			}
			v4s_total += NFS_DELTA(nfs.v4s[i]);
		    }
		    for (i = 54; i <= 70 && i < nfs_v4s_names_count; i++) {	/* NFS V4 Server */
			if (show_nfs == 3) {
			    mvwprintw(padnfs, 2 + i - 54, 59, "%12s%7.1f",
				      nfs_v4s_names[i],
				      NFS_DELTA(nfs.v4s[i]));
			}
			v4s_total += NFS_DELTA(nfs.v4s[i]);
		    }
		}
		mvwprintw(padnfs, 2 + 18, 1,
			  "--NFS-Totals->---Client----Server--");
		/* if(nfs_v2c_found || nfs_v2s_found) */
		mvwprintw(padnfs, 2 + 19, 1, "NFSv2 Totals->%9.1f %9.1f",
			  v2c_total, v2s_total);
		/* if(nfs_v3c_found || nfs_v3s_found) */
		mvwprintw(padnfs, 2 + 20, 1, "NFSv3 Totals->%9.1f %9.1f",
			  v3c_total, v3s_total);
		/* if(nfs_v4c_found || nfs_v4s_found) */
		mvwprintw(padnfs, 2 + 21, 1, "NFSv4 Totals->%9.1f %9.1f",
			  v4c_total, v4s_total);

		DISPLAY(padnfs, 24);
	    } else {
		if (nfs_first_time && !show_rrd) {
		    if (nfs_v2c_found) {
			fprintf(fp, "NFSCLIV2,NFS Client v2");
			for (i = 0; i < 18; i++)
			    fprintf(fp, ",%s", nfs_v2_names[i]);
			fprintf(fp, "\n");
		    }
		    if (nfs_v2s_found) {
			fprintf(fp, "NFSSVRV2,NFS Server v2");
			for (i = 0; i < 18; i++)
			    fprintf(fp, ",%s", nfs_v2_names[i]);
			fprintf(fp, "\n");
		    }

		    if (nfs_v3c_found) {
			fprintf(fp, "NFSCLIV3,NFS Client v3");
			for (i = 0; i < 22; i++)
			    fprintf(fp, ",%s", nfs_v3_names[i]);
			fprintf(fp, "\n");
		    }
		    if (nfs_v3s_found) {
			fprintf(fp, "NFSSVRV3,NFS Server v3");
			for (i = 0; i < 22; i++)
			    fprintf(fp, ",%s", nfs_v3_names[i]);
			fprintf(fp, "\n");
		    }

		    if (nfs_v4c_found) {
			fprintf(fp, "NFSCLIV4,NFS Client v4");
			for (i = 0; i < nfs_v4c_names_count; i++)
			    fprintf(fp, ",%s", nfs_v4c_names[i]);
			fprintf(fp, "\n");
		    }
		    if (nfs_v4s_found) {
			fprintf(fp, "NFSSVRV4,NFS Server v4");
			for (i = 0; i < nfs_v4s_names_count; i++)
			    fprintf(fp, ",%s", nfs_v4s_names[i]);
			fprintf(fp, "\n");
		    }
		    memcpy(&q->nfs, &p->nfs, sizeof(struct nfs_stat));
		    nfs_first_time = 0;
		}
		if (nfs_v2c_found) {
		    fprintf(fp,
			    show_rrd ? "rrdtool update nfscliv2.rrd %s" :
			    "NFSCLIV2,%s", LOOP);
		    for (i = 0; i < 18; i++) {
			fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
				(double) NFS_DELTA(nfs.v2c[i]));
		    }
		    fprintf(fp, "\n");
		}
		if (nfs_v2s_found) {
		    fprintf(fp,
			    show_rrd ? "rrdtool update nfsvrv2.rrd %s" :
			    "NFSSVRV2,%s", LOOP);
		    for (i = 0; i < 18; i++) {
			fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
				(double) NFS_DELTA(nfs.v2s[i]));
		    }
		    fprintf(fp, "\n");
		}
		if (nfs_v3c_found) {
		    fprintf(fp,
			    show_rrd ? "rrdtool update nfscliv3.rrd %s" :
			    "NFSCLIV3,%s", LOOP);
		    for (i = 0; i < 22; i++) {
			fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
				(double) NFS_DELTA(nfs.v3c[i]));
		    }
		    fprintf(fp, "\n");
		}
		if (nfs_v3s_found) {
		    fprintf(fp,
			    show_rrd ? "rrdtool update nfsvrv3.rrd %s" :
			    "NFSSVRV3,%s", LOOP);
		    for (i = 0; i < 22; i++) {
			fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
				(double) NFS_DELTA(nfs.v3s[i]));
		    }
		    fprintf(fp, "\n");
		}

		if (nfs_v4c_found) {
		    fprintf(fp,
			    show_rrd ? "rrdtool update nfscliv4.rrd %s" :
			    "NFSCLIV4,%s", LOOP);
		    for (i = 0; i < nfs_v4c_names_count; i++) {
			fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
				(double) NFS_DELTA(nfs.v4c[i]));
		    }
		    fprintf(fp, "\n");
		}
		if (nfs_v4s_found) {
		    fprintf(fp,
			    show_rrd ? "rrdtool update nfsvrv4.rrd %s" :
			    "NFSSVRV4,%s", LOOP);
		    for (i = 0; i < nfs_v4c_names_count; i++) {
			fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
				(double) NFS_DELTA(nfs.v4s[i]));
		    }
		    fprintf(fp, "\n");
		}
	    }
	}
	if (show_net) {
	    if (cursed) {
		BANNER(padnet, "Network I/O");
#define RKB 9
#define TKB 19
#define PIN 30
#define POUT 37
#define SIN 45
#define SOUT 52
#define PKHEAD 60
#define PKIN 66
#define PKOUT 71
/*
							  1         2         3         4         5         6         7
						01234567890123456789012345678901234567890123456789012345678901234567890123456789
			mvwprintw(padnet,1, 0, "I/F Name Recv=KB/s Trans=KB/s packin packout insize outsize Peak->Recv Trans");
*/
		COLOUR wattrset(padnet, COLOR_PAIR(0));
		mvwprintw(padnet, 1, 0, "I/F Name");
		COLOUR wattrset(padnet, COLOR_PAIR(2));
		mvwprintw(padnet, 1, RKB, "Recv=KB/s");
		COLOUR wattrset(padnet, COLOR_PAIR(3));
		mvwprintw(padnet, 1, TKB, "Trans=KB/s");
		COLOUR wattrset(padnet, COLOR_PAIR(2));
		mvwprintw(padnet, 1, PIN, "packin");
		COLOUR wattrset(padnet, COLOR_PAIR(3));
		mvwprintw(padnet, 1, POUT, "packout");
		COLOUR wattrset(padnet, COLOR_PAIR(2));
		mvwprintw(padnet, 1, SIN, "insize");
		COLOUR wattrset(padnet, COLOR_PAIR(3));
		mvwprintw(padnet, 1, SOUT, "outsize");
		COLOUR wattrset(padnet, COLOR_PAIR(0));
		mvwprintw(padnet, 1, PKHEAD, "Peak->");
		COLOUR wattrset(padnet, COLOR_PAIR(2));
		mvwprintw(padnet, 1, PKIN, "Recv");
		COLOUR wattrset(padnet, COLOR_PAIR(3));
		mvwprintw(padnet, 1, PKOUT, "Trans");
		COLOUR wattrset(padnet, COLOR_PAIR(0));
	    }
	    proc_net();
	    for (i = 0; i < networks; i++) {

#define IFDELTA(member) ((float)( (q->ifnets[i].member > p->ifnets[i].member) ? 0 : (p->ifnets[i].member - q->ifnets[i].member)/elapsed) )
#define IFDELTA_ZERO(member1,member2) ((IFDELTA(member1) == 0) || (IFDELTA(member2)== 0)? 0.0 : IFDELTA(member1)/IFDELTA(member2) )

		if (net_read_peak[i] < IFDELTA(if_ibytes) / 1024.0)
		    net_read_peak[i] = IFDELTA(if_ibytes) / 1024.0;
		if (net_write_peak[i] < IFDELTA(if_obytes) / 1024.0)
		    net_write_peak[i] = IFDELTA(if_obytes) / 1024.0;
/*
	  1         2         3         4         5         6         7
01234567890123456789012345678901234567890123456789012345678901234567890123456789
I/F Name Recv=KB/s Trans=KB/s packin packout insize outsize Peak->Recv Trans 
    eth3     0.0     0.0       0.0      0.0     0.0    0.0       0.0      0.0
      lo     0.0     0.0       0.0      0.0     0.0    0.0       0.0      0.0
    eth2     0.5     0.2       8.5      0.5    64.0  314.0      53.4     24.6
    eth1     0.0     0.0       0.0      0.0     0.0    0.0       0.0      0.0
    eth0     0.0     0.0       0.0      0.0     0.0    0.0       0.0      0.0          
*/
	        if (cursed) {
		COLOUR wattrset(padnet, COLOR_PAIR(0));
		mvwprintw(padnet, 2 + i, 0, "%8s",
			  &p->ifnets[i].if_name[0]);
		COLOUR wattrset(padnet, COLOR_PAIR(2));
		mvwprintw(padnet, 2 + i, RKB, "%8.1f",
			  IFDELTA(if_ibytes) / 1024.0);
		COLOUR wattrset(padnet, COLOR_PAIR(3));
		mvwprintw(padnet, 2 + i, TKB, "%8.1f",
			  IFDELTA(if_obytes) / 1024.0);
		COLOUR wattrset(padnet, COLOR_PAIR(2));
		mvwprintw(padnet, 2 + i, PIN, "%7.1f",
			  IFDELTA(if_ipackets));
		COLOUR wattrset(padnet, COLOR_PAIR(3));
		mvwprintw(padnet, 2 + i, POUT, "%7.1f",
			  IFDELTA(if_opackets));
		COLOUR wattrset(padnet, COLOR_PAIR(2));
		mvwprintw(padnet, 2 + i, SIN, "%7.1f",
			  IFDELTA_ZERO(if_ibytes, if_ipackets));
		COLOUR wattrset(padnet, COLOR_PAIR(3));
		mvwprintw(padnet, 2 + i, SOUT, "%7.1f",
			  IFDELTA_ZERO(if_obytes, if_opackets));
		COLOUR wattrset(padnet, COLOR_PAIR(2));
		mvwprintw(padnet, 2 + i, PKIN - 4, "%8.1f",
			  net_read_peak[i]);
		COLOUR wattrset(padnet, COLOR_PAIR(3));
		mvwprintw(padnet, 2 + i, PKOUT, "%8.1f",
			  net_write_peak[i]);
		}
	    }
	    DISPLAY(padnet, networks + 2);
	    if (!cursed) {
		fprintf(fp,
			show_rrd ? "rrdtool update net.rrd %s" : "NET,%s",
			LOOP);
		for (i = 0; i < networks; i++) {
		    fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
			    IFDELTA(if_ibytes) / 1024.0);
		}
		for (i = 0; i < networks; i++) {
		    fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
			    IFDELTA(if_obytes) / 1024.0);
		}
		fprintf(fp, "\n");
		fprintf(fp,
			show_rrd ? "rrdtool update netpacket.rrd %s" :
			"NETPACKET,%s", LOOP);
		for (i = 0; i < networks; i++) {
		    fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
			    IFDELTA(if_ipackets));
		}
		for (i = 0; i < networks; i++) {
		    fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
			    IFDELTA(if_opackets));
		}
		fprintf(fp, "\n");
	    }
	}
	errors = 0;
	for (i = 0; i < networks; i++) {
	    errors += p->ifnets[i].if_ierrs - q->ifnets[i].if_ierrs
		+ p->ifnets[i].if_oerrs - q->ifnets[i].if_oerrs
		+ p->ifnets[i].if_ocolls - q->ifnets[i].if_ocolls;
	}
	if (errors)
	    show_neterror = 3;
	if (show_neterror) {
	    if (cursed) {
		BANNER(padneterr, "Network Error Counters");
		mvwprintw(padneterr, 1, 0,
			  "I/F Name iErrors iDrop iOverrun iFrame oErrors   oDrop oOverrun oCarrier oColls ");
	    }
	    for (i = 0; i < networks; i++) {
		CURSE mvwprintw(padneterr, 2 + i, 0,
				"%8s %7lu %7lu %7lu %7lu %7lu %7lu %7lu %7lu %7lu",
				&p->ifnets[i].if_name[0],
				p->ifnets[i].if_ierrs,
				p->ifnets[i].if_idrop,
				p->ifnets[i].if_ififo,
				p->ifnets[i].if_iframe,
				p->ifnets[i].if_oerrs,
				p->ifnets[i].if_odrop,
				p->ifnets[i].if_ofifo,
				p->ifnets[i].if_ocarrier,
				p->ifnets[i].if_ocolls);

	    }
	    DISPLAY(padneterr, networks + 2);
	    if (show_neterror > 0)
		show_neterror--;
	}

	if (show_jfs) {
	    if (cursed) {
		BANNER(padjfs, "File Systems");
		mvwprintw(padjfs, 1, 0, "Filesystem            SizeMB  FreeMB  Use%% Type     MountPoint");

		for (k =0, j = 0; k < JFSMAX && j < jfses; k++) {
		    fs_size = 0;
		    fs_bsize = 0;
		    fs_free = 0;
		    fs_size_used = 100.0;
		    if (jfs[k].mounted == 0) 
			continue;
		    if (!strncmp(jfs[k].name, "/proc/", 6)	/* sub directorys have to be fake too */
			    ||!strncmp(jfs[k].name, "/sys/", 5)
			    || !strncmp(jfs[k].name, "/dev/", 5)
			    || !strncmp(jfs[k].name, "/proc", 6)	/* one more than the string to ensure the NULL */
			    ||!strncmp(jfs[k].name, "/sys", 5)
			    || !strncmp(jfs[k].name, "/dev", 5)
                            || !strncmp(jfs[i].name, "/var/lib/nfs/rpc", 16)
			    || !strncmp(jfs[k].name, "/rpc_pipe", 10)
			    ) {	/* /proc gives invalid/insane values */
			         if(show_jfs_minimum)  /* just skip outputing this JFS */
				     continue;
				 mvwprintw(padjfs, 2 + j, 0, "%-14s", jfs[k].name);
				 mvwprintw(padjfs, 2 + j, 27, "-");
				 mvwprintw(padjfs, 2 + j, 35, "-");
				 mvwprintw(padjfs, 2 + j, 41, "-");
				 COLOUR wattrset(padjfs, COLOR_PAIR(4));
				 mvwprintw(padjfs, 2 + j, 43, "%-8s not a real filesystem", jfs[k].type);
				 COLOUR wattrset(padjfs, COLOR_PAIR(0));
		    } else {
			    statfs_buffer.f_blocks = 0;
			    if ((ret =
				 fstatfs(jfs[k].fd,
					 &statfs_buffer)) != -1) {
				if (statfs_buffer.f_blocks != 0) {
				    /* older Linux seemed to always report in 4KB blocks but
				       newer Linux release use the f_bsize block sizes but
				       the man statfs docs the field as the natural I/O size so
				       the blocks reported here are ambigous in size */
				    if (statfs_buffer.f_bsize == 0)
					fs_bsize = 4.0 * 1024.0;
				    else
					fs_bsize = statfs_buffer.f_bsize;
				    /* convert blocks to MB */
				    fs_size =
					(float) statfs_buffer.f_blocks *
					fs_bsize / 1024.0 / 1024.0;

				    /* find the best size info available f_bavail is like df reports
				       otherwise use f_bsize (this includes inode blocks) */
				    if (statfs_buffer.f_bavail == 0)
					fs_free =
					    (float) statfs_buffer.f_bfree *
					    fs_bsize / 1024.0 / 1024.0;
				    else
					fs_free =
					    (float) statfs_buffer.
					    f_bavail * fs_bsize / 1024.0 /
					    1024.0;

				    /* this is a percentage */
				    fs_size_used =
					(fs_size -
					 (float) statfs_buffer.f_bfree *
					 fs_bsize / 1024.0 / 1024.0) /
					fs_size * 100.0;
				    /* try to get the same number as df using kludge */
				    /*fs_size_used += 1.0; */
				    if (fs_size_used > 100.0)
					fs_size_used = 100.0;

				    if ((i = strlen(jfs[k].device)) < 20)
					str_p = &jfs[k].device[0];
				    else {
					str_p = &jfs[k].device[i - 20];
				    }
				    mvwprintw(padjfs, 2 + j, 0,
					      "%-20s %7.0f %7.0f %4.0f%% %-8s %s",
					      str_p, fs_size, fs_free,
					      ceil(fs_size_used),
					      jfs[k].type, jfs[k].name);

				} else {
				    mvwprintw(padjfs, 2 + j, 0, "%s",
					      jfs[k].name);
				    COLOUR wattrset(padjfs, COLOR_PAIR(5));
				    mvwprintw(padjfs, 2 + j, 43,
					      "%-8s size=zero blocks!",
					      jfs[k].type);
				    COLOUR wattrset(padjfs, COLOR_PAIR(0));
				}
			    } else {
				mvwprintw(padjfs, 2 + j, 0, "%s",
					  jfs[k].name);
				COLOUR wattrset(padjfs, COLOR_PAIR(3));
				mvwprintw(padjfs, 2 + j, 43,
					  "%-8s statfs failed",
					  jfs[k].type);
				COLOUR wattrset(padjfs, COLOR_PAIR(0));
			    }
			}
		    j++;
		    }
		DISPLAY(padjfs, 2 + j);
	    } else {
		jfs_load(LOAD);
		fprintf(fp,
			show_rrd ? "rrdtool update jfsfile.rrd %s" :
			"JFSFILE,%s", LOOP);
		for (k = 0; k < jfses; k++) {
		    if (jfs[k].mounted && strncmp(jfs[k].name, "/proc", 5)
			&& strncmp(jfs[k].name, "/sys", 4)
			&& strncmp(jfs[k].name, "/dev/", 5)
			&& strncmp(jfs[k].name, "/run/", 5)
			&& strncmp(jfs[k].name, "/var/lib/nfs/rpc", 16)
			) {	/* /proc gives invalid/insane values */
			if (fstatfs(jfs[k].fd, &statfs_buffer) != -1) {
			    if (statfs_buffer.f_bsize == 0)
				fs_bsize = 4.0 * 1024.0;
			    else
				fs_bsize = statfs_buffer.f_bsize;
			    /* convert blocks to MB */
			    fs_size =
				(float) statfs_buffer.f_blocks * fs_bsize /
				1024.0 / 1024.0;

			    /* find the best size info available f_bavail is like df reports
			       otherwise use f_bsize (this includes inode blocks) */
			    if (statfs_buffer.f_bavail == 0)
				fs_free =
				    (float) statfs_buffer.f_bfree *
				    fs_bsize / 1024.0 / 1024.0;
			    else
				fs_free =
				    (float) statfs_buffer.f_bavail *
				    fs_bsize / 1024.0 / 1024.0;



			    if (fs_size <= 0.0 || fs_bsize <= 0.0)	/* some pseudo filesystems have zero size but we get a -nan result */
				fs_size_used = 0.0;
			    else
				fs_size_used =
				    (fs_size -
				     (float) statfs_buffer.f_bfree *
				     fs_bsize / 1024.0 / 1024.0) /
				    fs_size * 100.0;

			    if (fs_size_used > 100.0)
				fs_size_used = 100.0;

			    fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
				    fs_size_used);
			} else
			    fprintf(fp, show_rrd ? ":U" : ",0.0");
		    }
		}
		fprintf(fp, "\n");
		jfs_load(UNLOAD);
	    }
	}

	if (show_disk || show_verbose || show_diskmap || show_dgroup) {
	    proc_read(P_STAT);
	    proc_disk(elapsed);
	}
	if (show_diskmap) {
	    BANNER(padmap, "Disk %%Busy Map");
	    mvwprintw(padmap, 0, 18,
		      "Key: @=90 #=80 X=70 8=60 O=50 0=40 o=30 +=20 -=10 .=5 _=0%%");
	    mvwprintw(padmap, 1, 0,
		      "             Disk No.  1         2         3         4         5         6   ");
	    if (disk_first_time) {
		disk_first_time = 0;
		mvwprintw(padmap, 2, 0,
			  "Please wait - collecting disk data");
	    } else {
		mvwprintw(padmap, 2, 0,
			  "Disks=%-4d   0123456789012345678901234567890123456789012345678901234567890123",
			  disks);
		mvwprintw(padmap, 3, 0, "disk 0 to 63 ");
		for (i = 0; i < disks; i++) {
		    disk_busy = DKDELTA(dk_time) / elapsed;
		    disk_read = DKDELTA(dk_rkb) / elapsed;
		    disk_write = DKDELTA(dk_wkb) / elapsed;
		    /* ensure boundaries */
		    if (disk_busy < 0)
			disk_busy = 0;
		    else if (disk_busy > 99)
			disk_busy = 99;

#define MAPWRAP 64
		    mvwprintw(padmap, 3 + (int) (i / MAPWRAP),
			      13 + (i % MAPWRAP), "%c",
			      disk_busy_map_ch[(int) disk_busy]);
		}
	    }
	    DISPLAY(padmap, 4 + disks / MAPWRAP);
	}
	if (show_verbose) {
	    top_disk_busy = 0.0;
	    top_disk_name = "";
	    for (i = 0, k = 0; i < disks; i++) {
		disk_busy = DKDELTA(dk_time) / elapsed;
		if (disk_busy > top_disk_busy) {
		    top_disk_busy = disk_busy;
		    top_disk_name = p->dk[i].dk_name;
		}
	    }
	    if (top_disk_busy > 80.0) {
		COLOUR wattrset(padverb, COLOR_PAIR(1));
		mvwprintw(padverb, 3, 0, " DANGER");
	    } else if (top_disk_busy > 60.0) {
		COLOUR wattrset(padverb, COLOR_PAIR(4));
		mvwprintw(padverb, 3, 0, "Warning");
	    } else {
		COLOUR wattrset(padverb, COLOR_PAIR(2));
		mvwprintw(padverb, 3, 0, "     OK");
	    }
	    COLOUR wattrset(padverb, COLOR_PAIR(0));
	    mvwprintw(padverb, 3, 8,
		      "-> Top Disk %8s %%busy %5.1f%%\t>40%%\t>60%%          ",
		      top_disk_name, top_disk_busy);
	    move(x, 0);
	}
	if (show_disk) {
	    if (cursed) {
		if (show_disk) {
		    BANNER(paddisk, "Disk I/O");
		    switch (disk_mode) {
		    case DISK_MODE_PARTITIONS:
			mvwprintw(paddisk, 0, 12, "/proc/partitions");
			break;
		    case DISK_MODE_DISKSTATS:
			mvwprintw(paddisk, 0, 12, "/proc/diskstats");
			break;
		    case DISK_MODE_IO:
			mvwprintw(paddisk, 0, 12, "/proc/stat+disk_io");
			break;
		    }
		    mvwprintw(paddisk, 0, 31, "mostly in KB/s");
		    mvwprintw(paddisk, 0, 50,
			      "Warning:contains duplicates");
		    switch (show_disk) {
		    case SHOW_DISK_STATS:
			mvwprintw(paddisk, 1, 0, "DiskName Busy");
			COLOUR wattrset(paddisk, COLOR_PAIR(6));
			mvwprintw(paddisk, 1, 17, "Read");
			COLOUR wattrset(paddisk, COLOR_PAIR(3));
			mvwprintw(paddisk, 1, 25, "Write");
			COLOUR wattrset(paddisk, COLOR_PAIR(0));
			mvwprintw(paddisk, 1, 37,
				  "Xfers   Size  Peak%%  Peak=R+W    InFlight ");
			break;
		    case SHOW_DISK_GRAPH:
			mvwprintw(paddisk, 1, 0, "DiskName Busy  ");
			COLOUR wattrset(paddisk, COLOR_PAIR(6));
			mvwprintw(paddisk, 1, 15, "Read ");
			COLOUR wattrset(paddisk, COLOR_PAIR(3));
			mvwprintw(paddisk, 1, 20, "Write");
			COLOUR wattrset(paddisk, COLOR_PAIR(0));
			mvwprintw(paddisk, 1, 25,
				  "KB|0          |25         |50          |75       100|");
			break;
		    }
		}
		if (disk_first_time) {
		    disk_first_time = 0;
		    mvwprintw(paddisk, 2, 0,
			      "Please wait - collecting disk data");
		} else {
		    total_disk_read = 0.0;
		    total_disk_write = 0.0;
		    total_disk_xfers = 0.0;
		    disk_mb = 0;
		    for (i = 0, k = 0; i < disks; i++) {
			disk_read = DKDELTA(dk_rkb) / elapsed;
			disk_write = DKDELTA(dk_wkb) / elapsed;
			if ((show_disk == SHOW_DISK_GRAPH)
			    && (disk_read > 9999.9
				|| disk_write > 9999.9)) {
			    disk_mb = 1;
			    COLOUR wattrset(paddisk, COLOR_PAIR(1));
			    mvwprintw(paddisk, 1, 25, "MB");
			    COLOUR wattrset(paddisk, COLOR_PAIR(0));
			    break;
			}
		    }
		    for (i = 0, k = 0; i < disks; i++) {
			if (disk_only_mode
			    && is_dgroup_name(p->dk[i].dk_name) == 0)
			    continue;

/*
					if(p->dk[i].dk_name[0] == 'h')
						continue;
*/
			disk_busy = DKDELTA(dk_time) / elapsed;
			disk_read = DKDELTA(dk_rkb) / elapsed;
			disk_write = DKDELTA(dk_wkb) / elapsed;
			disk_xfers = DKDELTA(dk_xfers);

			total_disk_read += disk_read;
			total_disk_write += disk_write;
			total_disk_xfers += disk_xfers;

			if (disk_busy_peak[i] < disk_busy)
			    disk_busy_peak[i] = disk_busy;
			if (disk_rate_peak[i] < (disk_read + disk_write))
			    disk_rate_peak[i] = disk_read + disk_write;
			if (!show_all && disk_busy < 1)
			    continue;

			if (strlen(p->dk[i].dk_name) > 8)
			    str_p =
				&p->dk[i].
				dk_name[strlen(p->dk[i].dk_name) - 8];
			else
			    str_p = &p->dk[i].dk_name[0];

			if (show_disk == SHOW_DISK_STATS) {
			    /* output disks stats */
			    mvwprintw(paddisk, 2 + k, 0, "%-8s%4.0f%%",
				      str_p, disk_busy);
			    COLOUR wattrset(paddisk, COLOR_PAIR(6));
			    mvwprintw(paddisk, 2 + k, 13, "%9.1f",
				      disk_read);
			    COLOUR wattrset(paddisk, COLOR_PAIR(3));
			    mvwprintw(paddisk, 2 + k, 22, "%9.1fKB/s",
				      disk_write);
			    COLOUR wattrset(paddisk, COLOR_PAIR(5));
			    mvwprintw(paddisk, 2 + k, 36, "%6.1f", disk_xfers / elapsed);
			    COLOUR wattrset(paddisk, COLOR_PAIR(4));
			    mvwprintw(paddisk, 2 + k, 43, "%5.1fKB",
				      disk_xfers == 0.0 ? 0.0 : (DKDELTA(dk_rkb) + DKDELTA(dk_wkb)) / disk_xfers); 
			    COLOUR wattrset(paddisk, COLOR_PAIR(2));
			    mvwprintw(paddisk, 2 + k, 52,
				      "%3.0f%% %9.1fKB/s",
				      disk_busy_peak[i],
				      disk_rate_peak[i]);
			    COLOUR wattrset(paddisk, COLOR_PAIR(3));
			    mvwprintw(paddisk, 2 + k, 70, "%3d", p->dk[i].dk_inflight);
			    COLOUR wattrset(paddisk, COLOR_PAIR(0));
			    k++;
			}
			if (show_disk == SHOW_DISK_GRAPH) {
			    /* output disk bar graphs */
			    if (disk_mb) {
				disk_read_tmp = disk_read / 1024.0;
				disk_write_tmp = disk_write / 1024.0;
			    } else {
				disk_read_tmp = disk_read;
				disk_write_tmp = disk_write;
			    }

			    mvwprintw(paddisk, 2 + k, 0, "%-8s %3.0f%%",
				      str_p, disk_busy);
			    COLOUR wattrset(paddisk, COLOR_PAIR(6));
			    mvwprintw(paddisk, 2 + k, 13, "%7.1f",
				      disk_read_tmp);
			    COLOUR wattrset(paddisk, COLOR_PAIR(3));
			    mvwprintw(paddisk, 2 + k, 20, "%7.1f",
				      disk_write_tmp);
			    COLOUR wattrset(paddisk, COLOR_PAIR(0));

			    mvwprintw(paddisk, 2 + k, 27,
				      "|                                                  ");
			    wmove(paddisk, 2 + k, 28);
			    if (disk_busy > 100)
				disk_busy = 100;
			    if (disk_busy > 0.0
				&& (disk_write + disk_read) > 0.1) {
				/* 50 columns in the disk graph area so divide % by two */
				readers =
				    disk_busy * disk_read / (disk_write +
							     disk_read) /
				    2;
				writers =
				    disk_busy * disk_write / (disk_write +
							      disk_read) /
				    2;
				if (readers + writers > 50) {
				    readers = 0;
				    writers = 0;
				}
				/* don't go beyond row 78 i.e. j = 28 + 50 */
				for (j = 0; j < readers && j < 50; j++) {
				    COLOUR wattrset(paddisk,
						    COLOR_PAIR(12));
				    wprintw(paddisk, "R");
				    COLOUR wattrset(paddisk,
						    COLOR_PAIR(0));
				}
				for (; j < readers + writers && j < 50;
				     j++) {
				    COLOUR wattrset(paddisk,
						    COLOR_PAIR(11));
				    wprintw(paddisk, "W");
				    COLOUR wattrset(paddisk,
						    COLOR_PAIR(0));
				}
				for (j = disk_busy; j < 50; j++)
				    wprintw(paddisk, " ");
			    } else {
				for (j = 0; j < 50; j++)
				    wprintw(paddisk, " ");
				if (p->dk[i].dk_time == 0.0)
				    mvwprintw(paddisk, 2 + k, 27,
					      "| disk busy not available");
			    }
			    if (disk_busy_peak[i] > 100)
				disk_busy_peak[i] = 100;

			    mvwprintw(paddisk, 2 + i, 77, "|");
			    /* check rounding has not got the peak ">" over the 100% */
			    j = 28 + (int) (disk_busy_peak[i] / 2);
			    if (j > 77)
				j = 77;
			    mvwprintw(paddisk, 2 + i, j, ">");
			    k++;
			}
		    }
		    mvwprintw(paddisk, 2 + k, 0,
			      "Totals Read-MB/s=%-8.1f Writes-MB/s=%-8.1f Transfers/sec=%-8.1f",
			      total_disk_read / 1024.0,
			      total_disk_write / 1024.0,
			      total_disk_xfers / elapsed);

		}
		DISPLAY(paddisk, 3 + k);
	    } else {
		for (i = 0; i < disks; i++) {
		    if (NEWDISKGROUP(i))
			fprintf(fp,
				show_rrd ?
				"%srrdtool update diskbusy%s.rrd %s" :
				"%sDISKBUSY%s,%s", i == 0 ? "" : "\n",
				dskgrp(i), LOOP);
		    /* check percentage is correct */
		    ftmp = DKDELTA(dk_time) / elapsed;
		    if (ftmp > 100.0 || ftmp < 0.0)
			fprintf(fp, show_rrd ? ":U" : ",101.00");
		    else
			fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
				DKDELTA(dk_time) / elapsed);
		}
		for (i = 0; i < disks; i++) {
		    if (NEWDISKGROUP(i))
			fprintf(fp,
				show_rrd ?
				"\nrrdtool update diskread%s.rrd %s" :
				"\nDISKREAD%s,%s", dskgrp(i), LOOP);
		    fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
			    DKDELTA(dk_rkb) / elapsed);
		}
		for (i = 0; i < disks; i++) {
		    if (NEWDISKGROUP(i))
			fprintf(fp,
				show_rrd ?
				"\nrrdtool update diskwrite%s.rrd %s" :
				"\nDISKWRITE%s,%s", dskgrp(i), LOOP);
		    fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
			    DKDELTA(dk_wkb) / elapsed);
		}
		for (i = 0; i < disks; i++) {
		    if (NEWDISKGROUP(i))
			fprintf(fp,
				show_rrd ?
				"\nrrdtool update diskxfer%s.rrd %s" :
				"\nDISKXFER%s,%s", dskgrp(i), LOOP);
		    disk_xfers = DKDELTA(dk_xfers);
		    fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
			    disk_xfers / elapsed);
		}
		for (i = 0; i < disks; i++) {
		    if (NEWDISKGROUP(i))
			fprintf(fp,
				show_rrd ?
				"\nrrdtool update diskbsize%s.rrd %s" :
				"\nDISKBSIZE%s,%s", dskgrp(i), LOOP);
		    disk_xfers = DKDELTA(dk_xfers);
		    fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
			    disk_xfers == 0.0 ? 0.0 :
			    (DKDELTA(dk_rkb) +
			     DKDELTA(dk_wkb)) / disk_xfers);
		}

		if (extended_disk == 1 && disk_mode == DISK_MODE_DISKSTATS) {
		    for (i = 0; i < disks; i++) {
			if (NEWDISKGROUP(i)) {
			    fprintf(fp, "\nDISKREADS%s,%s", dskgrp(i),
				    LOOP);
			}
			disk_read = DKDELTA(dk_reads);
			fprintf(fp, ",%.1f", disk_read / elapsed);
		    }

		    for (i = 0; i < disks; i++) {
			if (NEWDISKGROUP(i)) {
			    fprintf(fp, "\nDISKWRITES%s,%s", dskgrp(i),
				    LOOP);
			}
			disk_write = DKDELTA(dk_writes);
			fprintf(fp, ",%.1f", disk_write / elapsed);
		    }
		}
		fprintf(fp, "\n");
	    }
	}
	if ((show_dgroup || (!cursed && dgroup_loaded))) {
	    if (cursed) {
		BANNER(paddg, "Disk Group I/O");
		if (dgroup_loaded != 2 || dgroup_total_disks == 0) {
		    mvwprintw(paddg, 1, 1,
			      "No Disk Groups found use -g groupfile when starting nmon");
		} else if (disk_first_time) {
		    disk_first_time = 0;
		    mvwprintw(paddg, 1, 1,
			      "Please wait - collecting disk data");
		} else {
		    mvwprintw(paddg, 1, 1,
			      "Name          Disks AvgBusy          |       TotalMB/s   xfers/s BlockSizeKB");
		    COLOUR wattrset(paddg, COLOR_PAIR(6));
		    mvwprintw(paddg, 1, 29, "Read-KB/s");
		    COLOUR wattrset(paddg, COLOR_PAIR(3));
		    mvwprintw(paddg, 1, 39, "Write");
		    COLOUR wattrset(paddg, COLOR_PAIR(0));
		    total_busy = 0.0;
		    total_rbytes = 0.0;
		    total_wbytes = 0.0;
		    total_xfers = 0.0;
		    for (k = n = 0; k < dgroup_total_groups; k++) {
/*
						if (dgroup_name[k] == 0 )
							continue;
*/
			disk_busy = 0.0;
			disk_read = 0.0;
			disk_write = 0.0;
			disk_xfers = 0.0;
			for (j = 0; j < dgroup_disks[k]; j++) {
			    i = dgroup_data[k * DGROUPITEMS + j];
			    if (i != -1) {
				disk_busy += DKDELTA(dk_time) / elapsed;
/*
								disk_read += DKDELTA(dk_reads) * p->dk[i].dk_bsize / 1024.0 /elapsed;
								disk_write += DKDELTA(dk_writes) * p->dk[i].dk_bsize / 1024.0 /elapsed;
*/
				disk_read += DKDELTA(dk_rkb) / elapsed;
				disk_write += DKDELTA(dk_wkb) / elapsed;
				disk_xfers += DKDELTA(dk_xfers) / elapsed;
			    }
			}
			if (dgroup_disks[k] == 0)
			    disk_busy = 0.0;
			else
			    disk_busy = disk_busy / dgroup_disks[k];
			total_busy += disk_busy;
			total_rbytes += disk_read;
			total_wbytes += disk_write;
			total_xfers += disk_xfers;
/*						if (!show_all && (disk_read < 1.0 && disk_write < 1.0))
							continue;
*/
			if ((disk_read + disk_write) == 0
			    || disk_xfers == 0)
			    disk_size = 0.0;
			else
			    disk_size =
				((float) disk_read +
				 (float) disk_write) / (float) disk_xfers;
			mvwprintw(paddg, n + 2, 1, "%-14s   %3d %5.1f%%          |          %6.1f %9.1f %6.1f ", dgroup_name[k], dgroup_disks[k], disk_busy, (disk_read + disk_write) / 1024,	/* in MB */
				  disk_xfers, disk_size);
			COLOUR wattrset(paddg, COLOR_PAIR(6));
			mvwprintw(paddg, n + 2, 29, "%9.1f", disk_read);
			COLOUR wattrset(paddg, COLOR_PAIR(3));
			mvwprintw(paddg, n + 2, 39, "%-9.1f", disk_write);
			COLOUR wattrset(paddg, COLOR_PAIR(0));
			n++;
		    }
		    mvwprintw(paddg, n + 2, 1, "Groups=%2d TOTALS %3d %5.1f%% %9.1f|%-9.1f %6.1f %9.1f", n, dgroup_total_disks, total_busy / dgroup_total_disks, total_rbytes, total_wbytes, (((double) total_rbytes + (double) total_wbytes)) / 1024,	/* in MB */
			      total_xfers);
		}
		DISPLAY(paddg, 3 + dgroup_total_groups);
	    } else {
		if (dgroup_loaded == 2) {
		    fprintf(fp,
			    show_rrd ? "rrdtool update dgbusy.rdd %s" :
			    "DGBUSY,%s", LOOP);
		    for (k = 0; k < dgroup_total_groups; k++) {
			if (dgroup_name[k] != 0) {
			    disk_total = 0.0;
			    for (j = 0; j < dgroup_disks[k]; j++) {
				i = dgroup_data[k * DGROUPITEMS + j];
				if (i != -1) {
				    disk_total +=
					DKDELTA(dk_time) / elapsed;
				}
			    }
			    fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
				    (float) (disk_total /
					     dgroup_disks[k]));
			}
		    }
		    fprintf(fp, "\n");
		    fprintf(fp,
			    show_rrd ? "rrdtool update dgread.rdd %s" :
			    "DGREAD,%s", LOOP);
		    for (k = 0; k < dgroup_total_groups; k++) {
			if (dgroup_name[k] != 0) {
			    disk_total = 0.0;
			    for (j = 0; j < dgroup_disks[k]; j++) {
				i = dgroup_data[k * DGROUPITEMS + j];
				if (i != -1) {
/*
									disk_total += DKDELTA(dk_reads) * p->dk[i].dk_bsize / 1024.0;
*/
				    disk_total += DKDELTA(dk_rkb);
				}
			    }
			    fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
				    disk_total / elapsed);
			}
		    }
		    fprintf(fp, "\n");
		    fprintf(fp,
			    show_rrd ? "rrdtool update dgwrite.rdd %s" :
			    "DGWRITE,%s", LOOP);
		    for (k = 0; k < dgroup_total_groups; k++) {
			if (dgroup_name[k] != 0) {
			    disk_total = 0.0;
			    for (j = 0; j < dgroup_disks[k]; j++) {
				i = dgroup_data[k * DGROUPITEMS + j];
				if (i != -1) {
/*
									disk_total += DKDELTA(dk_writes) * p->dk[i].dk_bsize / 1024.0;
*/
				    disk_total += DKDELTA(dk_wkb);
				}
			    }
			    fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
				    disk_total / elapsed);
			}
		    }
		    fprintf(fp, "\n");
		    fprintf(fp,
			    show_rrd ? "rrdtool update dgbsize.rdd %s" :
			    "DGSIZE,%s", LOOP);
		    for (k = 0; k < dgroup_total_groups; k++) {
			if (dgroup_name[k] != 0) {
			    disk_write = 0.0;
			    disk_xfers = 0.0;
			    for (j = 0; j < dgroup_disks[k]; j++) {
				i = dgroup_data[k * DGROUPITEMS + j];
				if (i != -1) {
/*
									disk_write += (DKDELTA(dk_reads) + DKDELTA(dk_writes) ) * p->dk[i].dk_bsize / 1024.0;
*/
				    disk_write +=
					(DKDELTA(dk_rkb) +
					 DKDELTA(dk_wkb));
				    disk_xfers += DKDELTA(dk_xfers);
				}
			    }
			    if (disk_write == 0.0 || disk_xfers == 0.0)
				disk_size = 0.0;
			    else
				disk_size = disk_write / disk_xfers;
			    fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
				    disk_size);
			}
		    }
		    fprintf(fp, "\n");
		    fprintf(fp,
			    show_rrd ? "rrdtool update dgxfer.rdd %s" :
			    "DGXFER,%s", LOOP);
		    for (k = 0; k < dgroup_total_groups; k++) {
			if (dgroup_name[k] != 0) {
			    disk_total = 0.0;
			    for (j = 0; j < dgroup_disks[k]; j++) {
				i = dgroup_data[k * DGROUPITEMS + j];
				if (i != -1) {
				    disk_total += DKDELTA(dk_xfers);
				}
			    }
			    fprintf(fp, show_rrd ? ":%.1f" : ",%.1f",
				    disk_total / elapsed);
			}
		    }
		    fprintf(fp, "\n");

		    if (extended_disk == 1
			&& disk_mode == DISK_MODE_DISKSTATS) {
			fprintf(fp, "DGREADS,%s", LOOP);
			for (k = 0; k < dgroup_total_groups; k++) {
			    if (dgroup_name[k] != 0) {
				disk_total = 0.0;
				for (j = 0; j < dgroup_disks[k]; j++) {
				    i = dgroup_data[k * DGROUPITEMS + j];
				    if (i != -1) {
					disk_total += DKDELTA(dk_reads);
				    }
				}
				fprintf(fp, ",%.1f", disk_total / elapsed);
			    }
			}
			fprintf(fp, "\n");
			fprintf(fp, "DGREADMERGE,%s", LOOP);
			for (k = 0; k < dgroup_total_groups; k++) {
			    if (dgroup_name[k] != 0) {
				disk_total = 0.0;
				for (j = 0; j < dgroup_disks[k]; j++) {
				    i = dgroup_data[k * DGROUPITEMS + j];
				    if (i != -1) {
					disk_total += DKDELTA(dk_rmerge);
				    }
				}
				fprintf(fp, ",%.1f", disk_total / elapsed);
			    }
			}
			fprintf(fp, "\n");
			fprintf(fp, "DGREADSERV,%s", LOOP);
			for (k = 0; k < dgroup_total_groups; k++) {
			    if (dgroup_name[k] != 0) {
				disk_total = 0.0;
				for (j = 0; j < dgroup_disks[k]; j++) {
				    i = dgroup_data[k * DGROUPITEMS + j];
				    if (i != -1) {
					disk_total += DKDELTA(dk_rmsec);
				    }
				}
				fprintf(fp, ",%.1f", disk_total / elapsed);
			    }
			}
			fprintf(fp, "\n");
			fprintf(fp, "DGWRITES,%s", LOOP);
			for (k = 0; k < dgroup_total_groups; k++) {
			    if (dgroup_name[k] != 0) {
				disk_total = 0.0;
				for (j = 0; j < dgroup_disks[k]; j++) {
				    i = dgroup_data[k * DGROUPITEMS + j];
				    if (i != -1) {
					disk_total += DKDELTA(dk_writes);
				    }
				}
				fprintf(fp, ",%.1f", disk_total / elapsed);
			    }
			}
			fprintf(fp, "\n");
			fprintf(fp, "DGWRITEMERGE,%s", LOOP);
			for (k = 0; k < dgroup_total_groups; k++) {
			    if (dgroup_name[k] != 0) {
				disk_total = 0.0;
				for (j = 0; j < dgroup_disks[k]; j++) {
				    i = dgroup_data[k * DGROUPITEMS + j];
				    if (i != -1) {
					disk_total += DKDELTA(dk_wmerge);
				    }
				}
				fprintf(fp, ",%.1f", disk_total / elapsed);
			    }
			}
			fprintf(fp, "\n");
			fprintf(fp, "DGWRITESERV,%s", LOOP);
			for (k = 0; k < dgroup_total_groups; k++) {
			    if (dgroup_name[k] != 0) {
				disk_total = 0.0;
				for (j = 0; j < dgroup_disks[k]; j++) {
				    i = dgroup_data[k * DGROUPITEMS + j];
				    if (i != -1) {
					disk_total += DKDELTA(dk_wmsec);
				    }
				}
				fprintf(fp, ",%.1f", disk_total / elapsed);
			    }
			}
			fprintf(fp, "\n");
			fprintf(fp, "DGINFLIGHT,%s", LOOP);
			for (k = 0; k < dgroup_total_groups; k++) {
			    if (dgroup_name[k] != 0) {
				disk_total = 0.0;
				for (j = 0; j < dgroup_disks[k]; j++) {
				    i = dgroup_data[k * DGROUPITEMS + j];
				    if (i != -1) {
					disk_total += p->dk[i].dk_inflight;
				    }
				}
				fprintf(fp, ",%.1f", disk_total);
			    }
			}
			fprintf(fp, "\n");
			fprintf(fp, "DGBACKLOG,%s", LOOP);
			for (k = 0; k < dgroup_total_groups; k++) {
			    if (dgroup_name[k] != 0) {
				disk_total = 0.0;
				for (j = 0; j < dgroup_disks[k]; j++) {
				    i = dgroup_data[k * DGROUPITEMS + j];
				    if (i != -1) {
					disk_total += DKDELTA(dk_backlog);
				    }
				}
				fprintf(fp, ",%.1f", disk_total / elapsed);
			    }
			}
			fprintf(fp, "\n");
		    }		/* if( extended_disk == 1 && disk_mode == DISK_MODE_DISKSTATS */
		}		/* if (dgroup_loaded == 2) */
	    }			/* else from if(cursed) */
	}
	/*          if ((show_dgroup || (!cursed && dgroup_loaded)))  */
	if (show_top) {
	    wmove(padtop, 1, 1);
	    wclrtobot(padtop);
	    /* Get the details of the running processes */
	    skipped = 0;
	    current_procs = getprocs(0);
	    if (current_procs > p->proc_records) {
		adjusted_procs = current_procs + 128;	/* allow for growth in the number of processes in the mean time */
		p->procs = REALLOC(p->procs, sizeof(struct procsinfo) * adjusted_procs);
		p->proc_records = adjusted_procs;
	    }

    	    p->processes = getprocs(p->proc_records); 

	    if (topper_size < p->processes) {
		topper = REALLOC(topper, sizeof(struct topper) * (p->processes +1));/* add one to avoid overrun */
		topper_size = p->processes;
	    }
	    /* Sort the processes by CPU utilisation */
	    for (i = 0, max_sorted = 0; i < p->processes; i++) {
		/* move forward in the previous array to find a match */
		for (j = 0; j < q->processes; j++) {
		    if (p->procs[i].pi_pid == q->procs[j].pi_pid) {	/* found a match */
			topper[max_sorted].index = i;
			topper[max_sorted].other = j;
			topper[max_sorted].time =
			    TIMEDELTA(pi_utime, i, j) + TIMEDELTA(pi_stime, i, j);
			topper[max_sorted].size =
			    p->procs[i].statm_resident;
			if (isroot && cursed) /* we don't sort on this in data capture */
			    topper[max_sorted].io =
				IODELTA(read_io, i, j) + IODELTA(write_io, i, j);

			max_sorted++;
			break;
		    }
		}
	    }
	    switch (show_topmode) {
	    default:
	    case 3:
		qsort((void *) &topper[0], max_sorted,
		      sizeof(struct topper), &cpu_compare);
		break;
	    case 4:
		qsort((void *) &topper[0], max_sorted,
		      sizeof(struct topper), &size_compare);
		break;
	    case 5:
		qsort((void *) &topper[0], max_sorted,
		      sizeof(struct topper), &disk_compare);
		break;
	    }
	    CURSE BANNER(padtop, "Top Processes");
	    if (isroot) {
		formatstring = "Procs=%d-mode=%d-1=Base 3=Perf 4=Size 5=I/O u=Args";
	    } else {
		formatstring = "Procs=%d-mode=%d-1=Base 3=Perf 4=Size 5=I/O[RootOnly] u=Args";
	   }
	    CURSE mvwprintw(padtop, 0, 15, formatstring, p->processes, show_topmode);
	    if (cursed && top_first_time) {
		top_first_time = 0;
		mvwprintw(padtop, 1, 1,
			  "Please wait - information being collected");
	    } else {
		switch (show_topmode) {
		case 1:   /* Basic */
		    if(cursed) {
		    mvwprintw(padtop, 1, 1,
				    "  PID      PPID  Pgrp Nice Prior Status     Proc-Flag   Command");
		    for (j = 0; j < max_sorted; j++) {
			i = topper[j].index;
			if (p->procs[i].pi_pgrp == p->procs[i].pi_pid)
			    strcpy(pgrp, "none");
			else
			    snprintf(&pgrp[0], 32, "%d", p->procs[i].pi_pgrp);
			/* skip over processes with 0 CPU */
			if (!show_all
			    && (topper[j].time / elapsed <
				ignore_procdisk_threshold) && !cmdfound)
			    break;
			if (x + j + 2 - skipped > LINES + 2)	/* +2 to for safety :-) */
			    break;
			mvwprintw(padtop, j + 2 - skipped, 1, "%7d %7d %6s",
					p->procs[i].pi_pid,
					p->procs[i].pi_ppid, 
					pgrp);
			COLOUR wattrset(padtop, COLOR_PAIR(5));
			mvwprintw(padtop, j + 2 - skipped, 24, "%4d %4d",
					p->procs[i].pi_nice,
					p->procs[i].pi_pri);
			if (topper[j].time * 100 / elapsed) {
				COLOUR wattrset(padtop, COLOR_PAIR(1));
			} else {
				COLOUR wattrset(padtop, COLOR_PAIR(2));
			}
			mvwprintw(padtop, j + 2 - skipped, 35, "%9s",
					(topper[j].time * 100 / elapsed) ? "Running " : get_state(p->procs[i].pi_state));

			COLOUR wattrset(padtop, COLOR_PAIR(6));
			mvwprintw(padtop, j + 2 - skipped, 45, "0x%08x",
					p->procs[i].pi_flags);
			COLOUR wattrset(padtop, COLOR_PAIR(1));
			mvwprintw(padtop, j + 2 - skipped, 54, "%1s",
					(p->procs[i].pi_tty_nr ? "F" : " "));
			COLOUR wattrset(padtop, COLOR_PAIR(3));
			mvwprintw(padtop, j + 2 - skipped, 57, "%-32s", p->procs[i].pi_comm);
			COLOUR wattrset(padtop, COLOR_PAIR(0));
			}
		    }
		    break;
		case 3:
		case 4:
		case 5:

		    if (show_args == ARGS_ONLY) {
			formatstring =
			    "  PID    %%CPU   ResSize Command                                            ";
		    } else if (COLS > 119) {
			if (show_topmode == 5)
			    formatstring =
				"  PID        %%CPU      Size       Res      Res       Res       Res      Shared       StorageKB  Command";
			else
			    formatstring =
				"  PID        %%CPU      Size       Res      Res       Res       Res      Shared   Faults   Faults Command";
		    } else {
			if (show_topmode == 5)
			    formatstring =
				"  PID    %%CPU  Size   Res   Res   Res   Res Shared StorageKB Command";
			else
			    formatstring =
				"  PID    %%CPU  Size   Res   Res   Res   Res Shared   Faults  Command";
		    }
		    CURSE mvwprintw(padtop, 1, y, formatstring);

		    if (show_args == ARGS_ONLY) {
			formatstring =
			    "         Used       KB                                                       ";
		    } else if (COLS > 119) {
			if (show_topmode == 5)
			    formatstring =
				"             Used        KB       Set      Text      Data       Lib        KB      Read   Write";
			else
			    formatstring =
				"             Used        KB       Set      Text      Data       Lib        KB      Min      Maj";
		    } else {
			if (show_topmode == 5)
			    formatstring =
				"         Used    KB   Set  Text  Data   Lib    KB ReadWrite ";
			else
			    formatstring =
				"         Used    KB   Set  Text  Data   Lib    KB  Min  Maj ";
		    }
		    CURSE mvwprintw(padtop, 2, 1, formatstring);
		    for (j = 0; j < max_sorted; j++) {
			i = topper[j].index;
			if (!show_all) {
			    /* skip processes with zero CPU/io */
			    if (show_topmode == 3
				&& (topper[j].time / elapsed) <
				ignore_procdisk_threshold && !cmdfound)
				break;
			    if (show_topmode == 5
				&& (topper[j].io < ignore_io_threshold
				    && !cmdfound))
				break;
			}
			if (cursed) {
			    if (x + j + 3 - skipped > LINES + 2)	/* +2 to for safety :-) XYZXYZ */
				break;
			    if (cmdfound && !cmdcheck(p->procs[i].pi_comm)) {
				skipped++;
				continue;
			    }
			    if (show_args == ARGS_ONLY) {

				mvwprintw(padtop, j + 3 - skipped, 1, "%7d", p->procs[i].pi_pid);
			        COLOUR wattrset(padtop, COLOR_PAIR(1));
				mvwprintw(padtop, j + 3 - skipped, 9, "%5.1f", topper[j].time / elapsed);
			        COLOUR wattrset(padtop, COLOR_PAIR(2));
				mvwprintw(padtop, j + 3 - skipped, 16, "%7lu", p->procs[i].statm_resident * pagesize / 1024);	/* in KB */
			        COLOUR wattrset(padtop, COLOR_PAIR(3));
				strncpy( truncated_command, args_lookup(p->procs[i].pi_pid, p->procs[i].pi_comm), 256);
				truncated_command[255] = 0; /* worst longest case */
				truncated_command[COLS - 24 - 2] = 0;
				
				mvwprintw(padtop, j + 3 - skipped, 24, "%-120s", truncated_command);
			        COLOUR wattrset(padtop, COLOR_PAIR(0));
			    } else {
				topsize = p->procs[i].statm_size * pagesize / 1024UL;		/* in KB */
				topsize_ch = ' ';
				toprset = p->procs[i].statm_resident * pagesize / 1024UL;	/* in KB */
				toprset_ch = ' ';
				toptrs = p->procs[i].statm_trs * pagesize / 1024UL;		/* in KB */
				toptrs_ch = ' ';
				topdrs = p->procs[i].statm_drs * pagesize / 1024UL;		/* in KB */
				topdrs_ch = ' ';
				toplrs = p->procs[i].statm_lrs * pagesize / 1024UL;		/* in KB */
				toplrs_ch = ' ';
				topshare = p->procs[i].statm_share * pagesize / 1024UL;		/* in KB */
				topshare_ch = ' ';
				toprio = (int) (COUNTDELTA(read_io) / elapsed / 1024);
				toprio_ch = ' ';
				topwio = (int) (COUNTDELTA(write_io) / elapsed / 1024);
				topwio_ch = ' ';
/*
				if (COLS > 119) 
				    formatstring = "%8d %8.1f %9lu%c%9lu%c%9lu%c%9lu%c%9lu%c%9lu%c%8d%c%8d%c%-32s"; 
				else  {
				    formatstring = "%7d %5.1f %5lu%c%5lu%c%5lu%c%5lu%c%5lu%c%5lu%c%4d%c%4d%c%-32s";
*/
				if (COLS < 119) {
				    if(topsize > 99999UL) {
					topsize = topsize / 1024UL;
					topsize_ch = 'm';
				    }
				    if(toprset > 99999UL) {
					toprset = toprset / 1024UL;
					toprset_ch = 'm';
				    }
				    if(toptrs > 99999UL) {
					toptrs = toptrs / 1024UL;
					toptrs_ch = 'm';
				    }
				    if(topdrs > 99999UL) {
					topdrs = topdrs / 1024UL;
					topdrs_ch = 'm';
				    }
				    if(toptrs > 99999UL) {
					toplrs = toplrs / 1024UL;
					toplrs_ch = 'm';
				    }
				    if(toptrs > 99999UL) {
					topshare = topshare / 1024UL;
					topshare_ch = 'm';
				    }
				    if(toprio > 99999UL) {
					toprio = toprio / 1024UL;
					topwio_ch = 'm';
				    }
				    if(topwio > 99999UL) {
					topwio = topwio / 1024UL;
					topwio_ch = 'm';
				    }
					/* now repeat incase we get many tens of GB sizes */
				    if(topsize > 99999UL) {
					topsize = topsize / 1024UL;
					topsize_ch = 'g';
				    }
				    if(toprset > 99999UL) {
					toprset = toprset / 1024UL;
					toprset_ch = 'g';
				    }
				    if(toptrs > 99999UL) {
					toptrs = toptrs / 1024UL;
					toptrs_ch = 'g';
				    }
				    if(topdrs > 99999UL) {
					topdrs = topdrs / 1024UL;
					topdrs_ch = 'g';
				    }
				    if(toptrs > 99999UL) {
					toplrs = toplrs / 1024UL;
					toplrs_ch = 'g';
				    }
				    if(toptrs > 99999UL) {
					topshare = topshare / 1024UL;
					topshare_ch = 'g';
				    }
				    if(toprio > 99999UL) {
					toprio = toprio / 1024UL;
					topwio_ch = 'g';
				    }
				    if(topwio > 99999UL) {
					topwio = topwio / 1024UL;
					topwio_ch = 'g';
				    }
				}

				mvwprintw(padtop, j + 3 - skipped, 1,                (COLS>119)?"%8d":"%7d",     p->procs[i].pi_pid);

			        COLOUR wattrset(padtop, COLOR_PAIR(1));
				mvwprintw(padtop, j + 3 - skipped, (COLS >119)?10:9, (COLS>119)?"%8.1f":"%5.1f", topper[j].time / elapsed);

			        COLOUR wattrset(padtop, COLOR_PAIR(2));
				mvwprintw(padtop, j + 3 - skipped, (COLS >119)?19:15, 
						(COLS>119)?"%9lu%c%9lu%c%9lu%c%9lu%c%9lu%c%9lu%c":"%5lu%c%5lu%c%5lu%c%5lu%c%5lu%c%5lu%c", 
					  topsize, topsize_ch,
					  toprset, toprset_ch,
					  toptrs, toptrs_ch,
					  topdrs, topdrs_ch,
					  toplrs, toplrs_ch,
					  topshare, topshare_ch);

				if(show_topmode == 5) {
			        COLOUR wattrset(padtop, COLOR_PAIR(5));
				mvwprintw(padtop, j + 3 - skipped, (COLS >119)?79:51, (COLS>119)?"%8d%c%8d%c":"%4d%c%4d%c", 
										(int)toprio, toprio_ch, (int)topwio, topwio_ch);
				} else {
			        COLOUR wattrset(padtop, COLOR_PAIR(6));
				mvwprintw(padtop, j + 3 - skipped, (COLS >119)?79:51, (COLS>119)?"%8d %8d":"%4d %4d", 
					  (int) (COUNTDELTA(pi_minflt) / elapsed), (int) (COUNTDELTA(pi_majflt) / elapsed) );
				}
			        COLOUR wattrset(padtop, COLOR_PAIR(3));
				mvwprintw(padtop, j + 3 - skipped, (COLS >119)?97:61, "%-32s", p->procs[i].pi_comm);
			        COLOUR wattrset(padtop, COLOR_PAIR(0));
			    }
			} else {
			    if ((cmdfound && cmdcheck(p->procs[i].pi_comm))
				|| (!cmdfound
				    && ((topper[j].time / elapsed) >
					ignore_procdisk_threshold))) {
#ifdef PRE_KERNEL_2_6_18
				fprintf(fp,
					"TOP,%07d,%s,%.2f,%.2f,%.2f,%lu,%lu,%lu,%lu,%lu,%d,%d,%s\n",
#else
				fprintf(fp,
					"TOP,%07d,%s,%.2f,%.2f,%.2f,%lu,%lu,%lu,%lu,%lu,%d,%d,%s,%ld,%llu\n",
#endif
					/* 1 */ p->procs[i].pi_pid,
					/* 2 */ LOOP,
					/* 3 */ topper[j].time / elapsed,
					/* 4 */ TIMEDELTA(pi_utime, i, topper[j].  other) / elapsed,
					/* 5 */ TIMEDELTA(pi_stime, i, topper[j].  other) / elapsed,
					/* 6 */ p->procs[i].statm_size * pagesize / 1024UL, /* in KB */
					/* 7 */ p->procs[i].statm_resident * pagesize / 1024UL, /* in KB */
					/* 8 */ p->procs[i].statm_trs * pagesize / 1024UL, /* in KB */
					/* 9 */ p->procs[i].statm_drs * pagesize / 1024UL, /* in KB */
					/* 10 */ p->procs[i].statm_share * pagesize / 1024UL, /* in KB */
					/* 11 */ (int) (COUNTDELTA(pi_minflt) / elapsed),
					/* 12 */ (int) (COUNTDELTA(pi_majflt) / elapsed),
					/* 13 */ p->procs[i].pi_comm
#ifdef PRE_KERNEL_2_6_18
				    );
#else
					,
					p->procs[i].pi_num_threads, COUNTDELTA(pi_delayacct_blkio_ticks)
				    );
#endif

				if (show_args)
				    args_output(p->procs[i].pi_pid, loop,
						p->procs[i].pi_comm);

			    } else
				skipped++;
			}
		    }
		    break;
		}
	    }
	    DISPLAY(padtop, 3 + j);
	}

	if (cursed) {
	    if (show_verbose) {
		y = x;
		x = 1;
		DISPLAY(padverb, 4);
		x = y;
	    }
	    /* underline the end of the stats area border */
	    if (x < LINES - 2)
		mvwhline(stdscr, x, 1, ACS_HLINE, COLS - 2);

	    wmove(stdscr, 0, 0);
	    wrefresh(stdscr);
	    doupdate();

	    for (i = 0; i < seconds; i++) {
		sleep(1);
		if (checkinput())
		    break;
	    }
	    if (x < LINES - 2)
		mvwhline(stdscr, x, 1, ' ', COLS - 2);
	    if (first_key_pressed == 0) {
		first_key_pressed = 1;
		wmove(stdscr, 0, 0);
		wclear(stdscr);
		wmove(stdscr, 0, 0);
		wclrtobot(stdscr);
		wrefresh(stdscr);
		doupdate();
	    }

	} else {
	    fflush(NULL);

	    gettimeofday(&nmon_tv, 0);
	    nmon_end_time =
		(double) nmon_tv.tv_sec +
		(double) nmon_tv.tv_usec * 1.0e-6;
	    if (nmon_run_time < 0.0) {
		nmon_start_time = nmon_end_time;
		nmon_run_time = 0.0;
	    }
	    nmon_run_time += (nmon_end_time - nmon_start_time);
	    if (nmon_run_time < 1.0) {
		secs = seconds;	/* sleep for the requested number of seconds */
	    } else {
		seconds_over = (int) nmon_run_time;	/* reduce the sleep time by whole number of seconds */
		secs = seconds - seconds_over;
		nmon_run_time -= (double) seconds_over;
	    }
	    if (secs < 1)	/* sanity check in case CPUs are flat out and nmon taking far to long to complete */
		secs = 1;

	  redo:
	    errno = 0;
	    ret = sleep(secs);
	    if ((ret != 0 || errno != 0) && loop != maxloops) {
		fprintf(fp,
			"ERROR,%s, sleep interrupted, sleep(%d seconds), return value=%d",
			LOOP, secs, ret);
		fprintf(fp, ", errno=%d\n", errno);
		secs = ret;
		goto redo;
	    }
	    gettimeofday(&nmon_tv, 0);
	    nmon_start_time =
		(double) nmon_tv.tv_sec +
		(double) nmon_tv.tv_usec * 1.0e-6;
	}

	switcher();

	if (loop >= maxloops) {
	    CURSE endwin();
	    if (nmon_end) {
		child_start(CHLD_END, nmon_end, time_stamp_type, loop,
			    timer);
		/* Give the end - processing some time - 5s for now */
		sleep(5);
	    }

	    fflush(NULL);
	    exit(0);
	}
    }
}
