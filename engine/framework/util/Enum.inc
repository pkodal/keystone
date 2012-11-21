<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

abstract class Enum
{
    final public function __construct($value)
    {
        $c = new ReflectionClass($this);
        if(!in_array($value, $c->getConstants())) 
        {
            throw new InvalidArgumentException("Invalid enum value '$value'");
        }
        $this->value = $value;
    }

    final public function __toString()
    {
        return strval($this->value);
    }

    final public function getValue()
    {
        return $this->value;
    }
 
    final public static function getSet()
    {
        $class = new ReflectionClass(get_called_class());
        
        $values = array();
        foreach ($class->getConstants() as $key => $constant)
        {
            // assume that if there is a '_' in the name, its a property, so exclude it
            if (strpos($key, '_') === false)
            {
                $values[] = $constant;
            }
        }
        
        return $values;
    }
    
    /**
     * Retrieve an associated 'property' of an enum instance.
     * 
     * @param string $propertyPostfix the postfix to find after the enum's variable name. i.e. for 'RESTURANT', if the
     * postfix is 'ICON' then we will retrieve the value of the const 'RESTURANT_ICON' stored in this class.
     * @return mixed the value of the property, or false if it cannot be found.
     */
    public function getProperty($propertyPostfix)
    {
        $c = new ReflectionClass($this);
        $constants = $c->getConstants();
        
        $matches = array_keys($constants, $this->value);
        if (count($matches) == 1)
        {
            $key = $matches[0] . '_' . $propertyPostfix;
            if (array_key_exists($key, $constants))
            {
                return $constants[$key];
            }
        }
        
        return false;
    }
}
?>
