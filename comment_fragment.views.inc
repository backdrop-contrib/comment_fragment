<?php
/**
 * @file
 * Views definitions for comment_fragment module.
 */
 
/**
 * Implements hook_views_data().
 */
function comment_fragment_views_data() {
  $data = array();
  $data['comment']['comment_fragment_view_comment'] = array(
    'field' => array(
      'title' => t('View SEO link'),
      'help' => t('Provide a link to view the comment, with a SEO path provided by Comment Fragment module'),
      'handler' => 'comment_fragment_handler_field_comment_link',
    ),
  );
  $data['comment']['comment_fragment_comment_path'] = array(
    'field' => array(
      'title' => t('Comment SEO path'),
      'help' => t('Provide a SEO path to the comment, provided by Comment Fragment module'),
      'handler' => 'comment_fragment_handler_field_comment_path',
    ),
  );
  return $data;
}
