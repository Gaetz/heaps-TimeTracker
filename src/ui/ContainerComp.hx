package ui;

import hxd.Res;
import utils.DateUtils;

@:uiComp("container")
class ContainerComp extends h2d.Flow implements h2d.domkit.Object {

	var font = Main.titleFont;
	inline static final timeTracker = "Time Tracker";

	static var SRC = <container>
		<layoutLine(70) class="titleLine">
			<bitmap src={Res.logo.toTile()} />
			<layoutCol(align) class="title">
				<title("Rufflerim", font) id="logoTitle"/>
				<text text={timeTracker} />
			</layoutCol>
			<layoutCol(align) class="date">
				<title("", font) public id="date" class="date" />
				<text text={"Week " + Std.string(DateUtils.getWeekOfYear())} />
			</layoutCol>
		</layoutLine>

		<layoutLine(200)>
			<layoutCol(align)>
				<view(align,[]) id="view"/>
				<text text="blop" />
			</layoutCol>

			<layoutCol(align)>
				<button public id="btn" />
				<text text="blop" />
			</layoutCol>

			<layoutCol(align)>
				<text text="blop" />
				<text text="blop" />
			</layoutCol>
		</layoutLine>

		<layoutLine(100)>
			<title("Today", font) />
			<button public id="btn1" />
			<button public id="btn2" />
			<text text="blop" />
			<text text="blop" />
		</layoutLine>

	</container>;



	public function new(align:h2d.Flow.FlowAlign, ?parent) {
		super(parent);
		initComponent();

	}

}

