<?php
/**
* @file
* Main page template.
*/
?>

<div id="branding" class="clearfix">
	<div id="branding-left">
	<?php print $breadcrumb; ?>

	<?php print render($title_prefix); ?>

	<?php if ($title): ?>
		<h1 class="page-title"><?php print $title; ?></h1>
	<?php endif; ?>

	<?php print render($title_suffix); ?>
	</div>
	<div id="branding-right">
		<div id="branding-right-inner">
		<?php if (isset($page['branding_right'])): ?>
			<?php print render($page['branding_right']); ?>
		<?php endif; ?>
		</div>
	</div>

</div>

<div id="navigation">

<?php if (isset($page['navigation'])): ?>
<div id="pre_local_tasks"><?php print render($page['navigation']); ?></div>
<?php endif; ?>

  <?php if ($primary_local_tasks): ?>
    <?php print render($primary_local_tasks); ?>
  <?php endif; ?>

  <?php if ($secondary_local_tasks): ?>
    <div class="tabs-secondary clearfix"><ul class="tabs secondary"><?php print render($secondary_local_tasks); ?></ul></div>
  <?php endif; ?>

</div>

<div id="page" class="idsims_document_num_translations_<?php print $idsims_document_num_translations; ?>">

	<div id="content" class="clearfix">
		<div class="element-invisible"><a id="main-content"></a></div>

	<?php if ($messages): ?>
		<div id="console" class="clearfix"><?php print $messages; ?></div>
	<?php endif; ?>

	<?php if ($page['help']): ?>
		<div id="help">
			<?php print render($page['help']); ?>
		</div>
	<?php endif; ?>

	<?php if (isset($page['content_before'])): ?>
		<div id="content-before">
			<?php print render($page['content_before']); ?>
		</div>
	<?php endif; ?>

	<?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>

  <div id="content-wrapper">

    <?php if (isset($page['sidebar_left'])): ?>
      <div id="sidebar-left">
        <?php print render($page['sidebar_left']); ?>
      </div>
    <?php endif; ?>

    <div id="main-content">
	    <?php print render($page['content']); ?>
	  </div>

    <?php if (isset($page['sidebar_right'])): ?>
      <div id="sidebar-right">
        <?php print render($page['sidebar_right']); ?>
      </div>
    <?php endif; ?>
	
	</div>

	<?php if (isset($page['content_after'])): ?>
		<div id="content-after">
			<?php print render($page['content_after']); ?>
		</div>
	<?php endif; ?>

	</div>

	<div id="footer">
		<?php print $feed_icons; ?>
	</div>

</div>

<?php if ($idsims_document_site_logo_url): ?>
  <style>
  	<?php print "#block-system-main { background-image:url('" . $idsims_document_site_logo_url ."'); }" ; ?>
  </style>
<?php endif; ?>
