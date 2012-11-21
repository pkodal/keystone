<?php
include_once(realpath(dirname(__FILE__) . '/../helperFunctions.inc'));

$_SERVER['REQUEST_METHOD'] = 'GET';
assert(isGetRequest());

$_SERVER['REQUEST_METHOD'] = 'POST';
assert(isPostRequest());

?>
