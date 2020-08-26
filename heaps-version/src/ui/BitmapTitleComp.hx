package ui;

@:uiComp("bitmapTitle")
// Naming scheme of component classes can be customized with domkit.Macros.registerComponentsPath();
class BitmapTitleComp extends h2d.Flow implements h2d.domkit.Object {

	var title:String;
	var font = Main.titleFont;

	static var SRC =
	<bitmapTitle>
		<bitmap src={tile} />
		<title(title, font) class="titleText" />
	</bitmapTitle>;

	public function new(title: String, tile: h2d.Tile, ?parent) {
		super(parent);
		initComponent();
		this.title = title;
	}

}