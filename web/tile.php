<?php

header('Content-Type: image/png');

if (!isset($_GET['z']) ||
	!isset($_GET['x']) ||
	!isset($_GET['y']) ||
	!isset($_GET['t']))
{
	die("Expecting z x y t");
}

$z = intval($_GET['z']);
$x = intval($_GET['x']);
$y = intval($_GET['y']);
$t = intval($_GET['t']);

passthru('gravmap ' .
	escapeshellarg($z) . ' ' .
	escapeshellarg($x) . ' ' .
	escapeshellarg($y) . ' ' .
	escapeshellarg($t));

?>
