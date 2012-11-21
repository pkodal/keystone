<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of PasswordGenerator
 *
 * @author Tima
 */
class PasswordGenerator
{
    public static function create($password)
    {
        return md5($password);
    }
}
?>
