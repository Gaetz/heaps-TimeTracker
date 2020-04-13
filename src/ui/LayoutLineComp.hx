package ui;

@:uiComp("layoutLine")
class LayoutLineComp extends h2d.Flow implements h2d.domkit.Object {

    var height:Int;
    static var SRC = <layoutLine height={height}></layoutLine>;

    public function new(height:Int, ?parent) {
        super(parent);
        initComponent();
        this.height = height;
    }
}