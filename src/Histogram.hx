import h2d.Object;
import dat.Data;

using Lambda;

enum HistoKind { ThisWeek; LastWeek; Overall; }

class Histogram extends Object {

    static final TICK = 360.; 

    var counter:Float;
    var lines:Array<HistoLine>;
    var kind:HistoKind;

    public override function new(kind, x, y, parent) {
        super(parent);
        this.kind = kind;
        this.x = x;
        this.y = y;
        lines = new Array<HistoLine>();
        var projects = Data.Projects.all;
        var count = 0;
        Lambda.iter(projects, (p) -> {
            var y = count * HistoBar.HEIGHT;
            lines.push(new HistoLine(y, p.Name, p.Color, this));
            count++;
        });
    }

    public function update(dt:Float) {
        counter += dt;
        if(counter >= TICK) {
            counter -= TICK;
            updateBars();
        }
    }

    function updateBars() {

    }

}