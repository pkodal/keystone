<div class="detailsBox2">
    <span class="debug-header">Modules</span><br/>
    <?=$validModules?> valid modules with controllers registered.

    <table>
        <tr>
            <td>Module</td><td>Controllers</td>
        </tr>

        <?php foreach ($modules as $moduleName => $module) { ?>
        <tr>
            <td class="item"><?=$moduleName?></td><td class="data"><?=join(', ', $module->getControllerClassNames())?></td>
        </tr>
        <?php } ?>
    </table>

    <br/><br/>
    Directories without control.inc (and are probably not modules):

    <p>
    <?php foreach ($nonModuleDirs as $dir) { ?>
        <span class="data"><?=$dir?></span><br/>
    <?php } ?>
    </p>

</div>