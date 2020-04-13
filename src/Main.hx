
/*
import dat.Data;
import hxd.Res;

class Main extends hxd.App {

    override function init() {
        Res.initEmbed();
        var tf = new h2d.Text(hxd.res.DefaultFont.get(), s2d);

		Data.load(haxe.Resource.getString("db/timeTracking.cdb"));
        tf.text = Data.Projects.get(tdad).Name;
    }

    static function main() {
        new Main();
    }
}
*/

import ui.*;

//PARAM=-lib domkit
class Main extends hxd.App {

	var center : h2d.Flow;
	var style = null;

	override function init() {
		center = new h2d.Flow(s2d);
		center.horizontalAlign = center.verticalAlign = Middle;
		onResize();
		var root = new ContainerComp(Right, center);

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
		#if hl
		hxd.res.Resource.LIVE_UPDATE = true;
		hxd.Res.initLocal();
		#else
		hxd.Res.initEmbed();
		#end
		new Main();
	}

}