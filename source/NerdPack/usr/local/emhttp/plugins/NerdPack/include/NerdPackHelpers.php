<?php
function format_size($value, $decimals, $unit='?') {
	if ($value == '')
		return 'unknown';

	/* Autodetect unit that's appropriate */
	if ($unit == '?') {
		if ($value >= 1099511627776)
			$unit = 'T';
		else
		if ($value >= (1 << 30))
			$unit = 'G';
		else
		if ($value >= (1 << 20))
			$unit = 'M';
		else
		if ($value >= (1 << 10))
			$unit = 'K';
		else
			$unit = 'B';
	}

	$unit = strtoupper($unit);

	switch ($unit) {
		case 'T': return number_format($value / (float)1099511627776, $decimals).' TB';
		case 'G': return number_format($value / (float)(1 << 30), $decimals).' GB';
		case 'M': return number_format($value / (float)(1 << 20), $decimals).' MB';
		case 'K': return number_format($value / (float)(1 << 10), $decimals).' kB';
		case 'B': return $value.' B';
	}

	return false;
}
?>
