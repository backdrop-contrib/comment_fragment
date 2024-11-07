<?php
/**
 * @file
 * Definition of comment_fragment_handler_field_comment_link.
 */

/**
 * Base field handler to present a link with a SEO path provided by Comment Fragment module.
 *
 * @ingroup views_field_handlers
 */
class comment_fragment_handler_field_comment_link extends views_handler_field_comment_link {
  function construct() {
    parent::construct();
  }
  
  function option_definition() {
    $options = parent::option_definition();
    $options['use_subject'] = array('default' => FALSE, 'bool' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['use_subject'] = array(
      '#title' => t('Use comment subject as text link (overrides "text to display" below).'),
      '#type' => 'checkbox',
      '#default_value' => $this->options['use_subject'],
    );
    parent::options_form($form, $form_state);
  }

  function render_link($data, $values) {
    $text = !empty($this->options['text']) ? $this->options['text'] : t('view');
    $comment = $this->get_value($values);
    $nid = $comment->nid;
    $cid = $comment->cid;
    $node_type = substr($comment->node_type, 13);
    $page = comment_get_display_page($cid, $node_type);

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['html'] = TRUE;

    if (!empty($cid)) {
      if ($this->options['use_subject']) {
        $text = $comment->subject;
      }
      $this->options['alter']['path'] = "node/" . $nid;
      $this->options['alter']['fragment'] = "comment-" . $cid;
      unset($this->options['alter']['query']['page']);
      if ($page) {
        $this->options['alter']['query']['page'] = $page;
      }
    }
    // If there is no comment link to the node.
    else if ($this->options['link_to_node']) {
      $this->options['alter']['path'] = "node/" . $nid;
    }

    return $text;
  }
}
