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