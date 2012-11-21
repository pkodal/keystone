<br/>
<div class="detailsBox3">
<span class="debug-header">Framework object Registry</span><br/>

Total objects: <?=$objectCount?><br/>
<table>
<tr>
<td><i>Key</i></td>
<td><i>Class name</i></td>
</tr>

<?php foreach($objects as $key => $objectClass) {?>
<tr>
<td class="item"><?=$key?></td><td class="data"><?=$objectClass?></td>
</tr>
<?php } ?>

</table>
</div>
<br/>