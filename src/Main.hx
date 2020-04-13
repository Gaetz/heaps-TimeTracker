
import dat.Data;
import hxd.Res;
import ui.*;

class Main extends hxd.App {

	var center : h2d.Flow;
	var style = null;
	var root : ContainerComp;

    override function init() {
        var tf = new h2d.Text(hxd.res.DefaultFont.get(), s2d);
		tf.text = Data.Projects.get(tdad).Name;

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

		// Override
		root.btn.label = "Button";
		root.btn1.label = "Highlight ON";
		root.btn2.labelTxt.text = "Highlight OFF";

		root.btn1.onClick = function() {
			root.btn.dom.addClass("highlight");
		}
		root.btn2.onClick = function() {
			root.btn.dom.removeClass("highlight");
		}
	}

	function initStyle() {
		style = new h2d.domkit.Style();
		style.load(hxd.Res.style);
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
