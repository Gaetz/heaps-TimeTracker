package ui;

@:uiComp("container")
class ContainerComp extends h2d.Flow implements h2d.domkit.Object {

	static var SRC = <container>
		<view(align,[]) id="view"/>
		<button public id="btn"/>
		<button public id="btn1"/>
		<button public id="btn2"/>
	</container>;

	public function new(align:h2d.Flow.FlowAlign, ?parent) {
		super(parent);
		initComponent();
	}

}