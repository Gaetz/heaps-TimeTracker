import h3d.Vector;
import h2d.Tile;
import h2d.Text;
using Lambda;

class HistoBar extends h2d.Bitmap {

    static final MAX_WIDTH = 150;
    public static final HEIGHT = 25;
    
    var hours:Float;
    var text:Text;

    public function new(color, parent) {
        var tile = Tile.fromColor(color);
        super(tile, parent);
        height = Constants.BAR_HEIGHT;
        width = 20;
        hours = 0;
        text = new Text(Main.textFont, this);
        text.color = new Vector(1, 1, 1, 1);
        text.text = Std.string(hours);
        text.x = Constants.BAR_TEXT_X_OFFSET;
        text.y = Constants.BAR_TEXT_Y_OFFSET;
    }

    public function updateSize(weeklyHours:Array<Float>, index) {
        hours = weeklyHours[index];
        var max = weeklyHours.fold(Math.max, weeklyHours[0]);
        var ratio = hours / max;
        width = Math.max(20, ratio * Constants.BAR_MAX_WIDTH);
        text.text = Std.string(hours);
        text.x = width - 15;
    }

}