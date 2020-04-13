package ui;

@:uiComp("view")
// Naming scheme of component classes can be customized with domkit.Macros.registerComponentsPath();
class ViewComp extends h2d.Flow implements h2d.domkit.Object {

	static var SRC =
	<view class="mybox" min-width="200" content-halign={align}>
		Hello World
		${
			for( i in icons )
				<bitmap src={i} id="icons[]"/>
		}
	</view>;

	public function new(align:h2d.Flow.FlowAlign,icons:Array<h2d.Tile>,?parent) {
		super(parent);
		initComponent();
	}

}