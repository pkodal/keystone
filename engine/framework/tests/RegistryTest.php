<?php
include_once(realpath(dirname(__FILE__) . '/../Registry.inc'));
include_once(realpath(dirname(__FILE__) . '/../Dispatcher.inc'));

$registry = Registry::getRegistry();

assert($registry != NULL);
assert(is_a($registry, 'Registry'));

$string = "im a string";
$dispatcher = Dispatcher::buildDispatcher();

$id1 = 'id1';
$id2 = 'id2';

$registry->store($id1, $string);
$registry->store($id2, $dispatcher);

assert($string  === $registry->fetch($id1));
assert($dispatcher  === $registry->fetch($id2));

assert($registry->objectExists($id1));
assert($registry->objectExists($id2));

assert($registry->fetch('scjsdncs') === FALSE);
assert(!$registry->objectExists('scjsdncs'));

$registry->store($id1, $dispatcher);
assert($dispatcher  === $registry->fetch($id1));

assert($registry->getLocalObjectCount() === 2);

assert(Registry::getRegistry()=== $registry);
assert(Registry::getRegistry()->getLocalObjectCount() === 2);

?>