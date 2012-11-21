<?php

class HtmlUtil
{
    public static function includeScript($scriptFile)
    {
        if (is_array($scriptFile))
        {
            $script = '';
            foreach($scriptFile as $file)
            {
                $script .= '<script type="text/javascript" src="'. $file .'"></script>';
            }
            return $script;
        }
        return '<script type="text/javascript" src="'. $scriptFile .'"></script>';
    }

    public static function includeCss($cssFile)
    {
        if (is_array($cssFile))
        {
            $css = '';
            foreach($cssFile as $file)
            {
                $css .= '<link rel="stylesheet" type="text/css" href="' . $file . '"/>';
            }
            return $css;
        }
        return '<link rel="stylesheet" type="text/css" href="' . $cssFile . '"/>';
    }


    public static function includeDynamicScript($scriptFile)
    {
        if (is_array($scriptFile))
        {
            $script = '';
            foreach($scriptFile as $file)
            {
                $script .= '<script>$.getScript("'. $file .'")</script>';
            }
            return $script;
        }
        return '<script>$.getScript("'. $scriptFile .'")</script>';
    }

    /**
     * Hepler method to create inline Javascript bootstrap code blocks.
     * @param string $js the javascript to run
     * @return string the javascript bootstrap block
     */
    public static function createBootstrapJs($js)
    {
        $bootstrapJs = <<< END
             <script type="text/javascript">
                jQuery(document).ready(function() {
                    $js
                });
            </script>
END;
        return $bootstrapJs;
    }

    /**
     * 
     * @param string $string
     * @return string
     */
    public static function escapeString($string)
    {
        return htmlspecialchars($string);
    }

    public static function stripQuotes($string)
    {
        return str_replace(array("'",'"',"\'", '\"'), "", $string);
    }
}

?>