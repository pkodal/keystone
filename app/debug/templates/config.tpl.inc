
<?php

function booleanString($bool)
{
    if ($bool)
    {
        return 'true';
    }

    return 'false';
}
?>


<div class="detailsBox">
<span class="debug-header">Framework config</span><br/>

<table>
<tr>
    <td class="item">REST query parameter</td><td class="data"><?=QUERY_PARAM?></td>
</tr>

<tr>
    <td class="item">Default module on startup</td><td class="data"><?=DEFAULT_MODULE?></td>
</tr>

<tr>
    <td class="item">Error controller</td><td class="data"><?=ERROR_CONTROLLER?></td>
</tr>

<tr>
    <td class="item">Verbose exception messages</td><td class="data"><?=booleanString(VERBOSE_EXCEPTIONS)?></td>
</tr>
</table>
</div>