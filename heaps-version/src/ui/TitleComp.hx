package ui;

import h2d.Font;

@:uiComp("title")
// Naming scheme of component classes can be customized with domkit.Macros.registerComponentsPath();
class TitleComp extends h2d.Flow implements h2d.domkit.Object {

	public var label(get, set): String;
	function get_label() return labelTxt.text;
	function set_label(s) {
		labelTxt.text = s;
		return s;
	}

	static var SRC =
	<title>
		<text class="title" font={font} public id="labelTxt" />
	</title>;

	public function new(text: String, font:Font, ?parent) {
		super(parent);
		initComponent();
		set_label(text);
	}

}