<?php
/**
 * @file
 * Definition of comment_fragment_handler_field_comment_path.
 */

/**
 * Base field handler to present a SEO path provided by Comment Fragment module.
 *
 * @ingroup views_field_handlers
 */
class comment_fragment_handler_field_comment_path extends views_handler_field_entity {
  function construct() {
    parent::construct();
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['absolute'] = array('default' => FALSE, 'bool' => TRUE);
    $options['link_to_node'] = array('default' => FALSE, 'bool' => TRUE);

    return $options;
  }
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['absolute'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use absolute path (begins with "http://")'),
      '#default_value' => $this->options['absolute'],
      '#description' => t('Enable this option to output an absolute path.'),
    );
    $form['link_to_node'] = array(
      '#title' => t('Provide the node path if there is no comment.'),
      '#type' => 'checkbox',
      '#default_value' => $this->options['link_to_node'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $value = $this->get_value($values, 'cid');
    return $this->render_path($this->sanitize_value($value), $values);
  }

  function render_path($data, $values) {
    $comment = $this->get_value($values);
    $nid = $comment->nid;
    $cid = $comment->cid;
    $node_type = substr($comment->node_type, 13);
    $page = comment_get_display_page($cid, $node_type);
    $options = array();
    $options['absolute'] = $this->options['absolute'];

    if (!empty($cid)) {
      $path = "node/" . $nid;
      $options['fragment'] = "comment-" . $cid;
      // unset($this->options['alter']['query']['page']);
      if ($page) {
        $options['query']['page'] = $page;
      }
    }
    // If there is no comment provide a path to the node.
    else if ($this->options['link_to_node']) {
      $path = "node/" . $nid;
    }

    return url($path, $options);
  }
}
