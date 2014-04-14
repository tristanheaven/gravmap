<?php

header('Content-Type: image/png');

if (!isset($_GET['z']) ||
	!isset($_GET['x']) ||
	!isset($_GET['y']))
{
	die("Expecting z x y");
}

$z = intval($_GET['z']);
$x = intval($_GET['x']);
$y = intval($_GET['y']);

passthru('grav ' .
	escapeshellarg($z) . ' ' .
	escapeshellarg($x) . ' ' .
	escapeshellarg($y));

?>
