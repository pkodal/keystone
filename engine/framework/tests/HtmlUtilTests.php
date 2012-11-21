<?php

include_once(realpath(dirname(__FILE__) . '/../HtmlUtil.inc'));

$cssFile = "foobar.css";
$expectedCss = '<link rel="stylesheet" type="text/css" href="' . $cssFile . '"/>';

assert(HtmlUtil::includeCss($cssFile) == $expectedCss);

$jsFile = "foobar.js";
$expectedJs = '<script type="text/javascript" src="'. $jsFile .'"></script>';

assert(HtmlUtil::includeScript($jsFile) == $expectedJs);

?>