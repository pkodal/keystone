<?php

set_include_path(get_include_path() . ':' . realpath(dirname(__FILE__)));
require_once (dirname(__FILE__) . '/Doctrine/Common/ClassLoader.php');

$classLoader = new \Doctrine\Common\ClassLoader('Doctrine');
$classLoader->register();

$classLoader = new \Doctrine\Common\ClassLoader('Symfony', 'Doctrine');
$classLoader->register();

$config = new \Doctrine\ORM\Configuration(); // (2)

// Proxy Configuration (3)
$config->setProxyDir(dirname(__FILE__) . '/proxies');
$config->setProxyNamespace(PROXY_NAMESPACE);
$config->setAutoGenerateProxyClasses(DEV_MODE);

// Mapping Configuration (4)

$driverImpl = $config->newDefaultAnnotationDriver($entities);
$config->setMetadataDriverImpl($driverImpl);


// Caching Configuration (5)
if (DEV_MODE)
{
    $cache = new \Doctrine\Common\Cache\ArrayCache();
}
else
{
    $cache = new \Doctrine\Common\Cache\ApcCache();
}
$config->setMetadataCacheImpl($cache);
$config->setQueryCacheImpl($cache);

// database configuration parameters (6)
$conn = array(
    'driver' => 'pdo_mysql',
    'host' => DB_HOST,
    'dbname' => DB_DATABASE_NAME,
    'user' => DB_USERNAME,
    'password' => DB_PASSWD
);
// obtaining the entity manager (7)
$evm = new Doctrine\Common\EventManager();
$entityManager = \Doctrine\ORM\EntityManager::create($conn, $config, $evm);

Registry::getRegistry()->store(ENTITY_MANAGER, $entityManager);

?>
