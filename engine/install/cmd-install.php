<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

$_SERVER['REQUEST_METHOD'] = 'POST';
if (array_key_exists(1, $argv))
{
    $_POST['password'] = $argv[1];
    echo 'password set';
}

include_once(dirname(__FILE__) .'/index.php');
?>
