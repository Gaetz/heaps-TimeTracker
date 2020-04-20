package ui;

@:uiComp("bar")
// Naming scheme of component classes can be customized with domkit.Macros.registerComponentsPath();
class BarComp extends h2d.Flow implements h2d.domkit.Object {

	static var SRC =
	<bar class="mybox" min-width="150" content-halign={align}>
		Hello World
	</bar>;

	public function new(align:h2d.Flow.FlowAlign, ?parent) {
		super(parent);
		initComponent();
	}

}