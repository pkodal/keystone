<?php
include_once(realpath(dirname(__FILE__) . '/../BasicResources.inc'));

// widget

$html = "<b>test html</b>";
$cssFile = "mycss.css";
$jsFile = "myjavascript.js";
$expectedWidget = '<link rel="stylesheet" type="text/css" href="mycss.css"/><script type="text/javascript" src="myjavascript.js"></script><b>test html</b>';

$widget = new WidgetResource($html, $cssFile, $jsFile);

assert(is_a($widget, 'Resource'));
assert($widget->containsCssFile());
assert($widget->containsJavascriptFile());
assert($widget->render() === $expectedWidget);

// json
$expectedJson = '{"key1":"value1","key2":"value2"}';
$expectedSimpleJson = '{"success":true,"data":"foodbar"}';

$json = new JsonResource();
$json->addField('key1', 'value1');
$json->addField('key2', 'value2');
assert($json->render() === $expectedJson);

$json = JsonResource::createSimpleJsonResource(true, 'foodbar');
assert($json->render() === $expectedSimpleJson);

?>