<?php


function isGetRequest()
{
	return ($_SERVER['REQUEST_METHOD'] == 'GET');
}

function isPostRequest()
{
	return ($_SERVER['REQUEST_METHOD'] == 'POST');
}


function isJsonType()
{
	return (preg_match('/application\/json/', $_SERVER['HTTP_ACCEPT']) !== 0);
}

function isHtmlType()
{
	return (preg_match('/text\/html/', $_SERVER['HTTP_ACCEPT']) !== 0);
}

function setNoCacheHeaders()
{
    header("Expires: Sun, 19 Nov 1978 05:00:00 GMT");
    header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
    header("Cache-Control: no-store, no-cache, must-revalidate");
    header("Cache-Control: post-check=0, pre-check=0", false);
    header("Pragma: no-cache");
}

?>