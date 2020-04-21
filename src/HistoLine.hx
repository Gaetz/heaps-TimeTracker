import h2d.Object;
import h2d.Text;

class HistoLine extends Object {

    var titleText:Text;
    var bar:HistoBar;

    public override function new(y, name, color, parent) {
        super(parent);
        this.y = y;
        titleText = new Text(Main.textFont, this);
        titleText.text = name;
        titleText.y += Constants.LINE_TEXT_Y_OFFSET;
        bar = new HistoBar(color, this);
        bar.x = Constants.LINE_TITLE_WIDTH;
    }

    public function updateLine(weeklyHours, index) {
        bar.updateSize(weeklyHours, index);
    }
}