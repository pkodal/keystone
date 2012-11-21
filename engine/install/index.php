<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

define('INSTALL', 'true');

include_once (realpath(dirname(__FILE__) . '/../bootstrap.inc'));
include_once (realpath(dirname(__FILE__) . '/SchemaGenerator.inc'));


function install($conn)
{
    $createUserSql = 'CREATE USER \''. DB_USERNAME .'\'@\'localhost\' IDENTIFIED BY \''. DB_PASSWD .'\'';
    $createDbSql = 'CREATE DATABASE '. DB_DATABASE_NAME;
    $grantAccessSql = 'GRANT ALL ON ' . DB_DATABASE_NAME .'.* TO \''. DB_USERNAME . '\'@\'localhost\' identified by \''.DB_PASSWD .'\'';

    mysql_query($createUserSql, $conn);
    mysql_query($createDbSql, $conn);
    mysql_query($grantAccessSql, $conn);
}

function dropInstall($conn)
{
   $checkDbSql = 'SELECT user FROM mysql.user WHERE user=\''.DB_DATABASE_NAME.'\'';
   $dropDbSql = 'DROP DATABASE '. DB_DATABASE_NAME;
   $dropUserSql = 'DROP USER '. DB_USERNAME;

   $resource = mysql_query($checkDbSql, $conn);

//   $result = mysql_num_rows($resource);

   if ($resource != false)
   {
       mysql_query($dropDbSql, $conn);
       mysql_query($dropUserSql, $conn);
   }
}



function run()
{
    if (!key_exists('password', $_POST))
    {
        return false;
    }
  
    $conn = mysql_connect(DB_HOST, 'root', $_POST['password']);
    dropInstall($conn);
    install($conn);
    mysql_close($conn);

    $schemaGenerator = new SchemaGenerator();
    $schemaGenerator->createSchema();

    return true;
}

?>

<?php if (isGetRequest()) { ?>

<form name="install" action="./index.php" method="post">
    database password: <input type="password" name="password" /><br/>
    <input type="submit" value="Install" />
</form>

<?php } else { if (run()) { ?>
<h1>Database Successfully installed!</h1>
<?php } else { ?>
<h1>Database Failed to install! </h1>    
<?php } } ?>
