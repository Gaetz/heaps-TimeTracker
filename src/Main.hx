
import dat.Data;
import hxd.Res;
import ui.*;
import h2d.Font;

class Main extends hxd.App {

	var center : h2d.Flow;
	var style = null;
	var root : ContainerComp;
	public static var titleFont: h2d.Font;
	public static var subtitleFont: h2d.Font;
	public static var textFont: h2d.Font;

    override function init() {
        //var tf = new h2d.Text(hxd.res.DefaultFont.get(), s2d);
		//tf.text = Data.Projects.get(tdad).Name;
		titleFont = Res.JetBrainsMonoBold.toFont();
		subtitleFont = Res.JetBrainsMonoMedium.toFont();
		textFont = hxd.res.DefaultFont.get();

		initUI();
		initStyle();
	}
	
	/**
	 * Init UI elements
	 */
	function initUI() {
		// Flow
		center = new h2d.Flow(s2d);
		center.horizontalAlign = center.verticalAlign = Middle;
		onResize();
		root = new ContainerComp(Right, center);

		var date = Date.now();
		var sb = new StringBuf();
		sb.add(date.getDate());
		sb.add("/");
		sb.add(date.getMonth() + 1);
		sb.add("/");		
		sb.add(date.getFullYear());
		var formatedDate = sb.toString();

		// Override
		//root.date.text.font = titleFont;
		root.btn.label = "Button";
		root.btn1.label = "Highlight ON";
		root.btn2.label = "Highlight OFF";
		root.date.label = formatedDate;

		root.btn1.onClick = function() {
			root.btn.dom.addClass("highlight");
		}
		root.btn2.onClick = function() {
			root.btn.dom.removeClass("highlight");
		}
	}

	function initStyle() {
		style = new h2d.domkit.Style();
		style.load(Res.style);
		style.addObject(root);
	}

	override function onResize() {
		center.minWidth = center.maxWidth = s2d.width;
		center.minHeight = center.maxHeight = s2d.height;
	}

	override function update(dt:Float) {
		style.sync();
	}

    static function main() {
		Res.initEmbed();
		Data.load(haxe.Resource.getString("db/timeTracking.cdb"));
        new Main();
    }
}
