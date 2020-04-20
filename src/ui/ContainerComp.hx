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

		<layoutLine(220)>
			<layoutCol(align)>
				<bar(align) id="view"/>
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

		<layoutLine(90)>
			<layoutCol(align)>
				<title("Today", font) />
			</layoutCol>

			<layoutCol(align)>
				<layoutLine(20) class="smallLine">
					<button public id="checkPomodoro" class="checkbox" />
					<text text="Pomorodo" />
					<button public id="checkRing" class="checkbox" />
					<text text="Ring" />
				</layoutLine>
				<button public id="start" class="start" />
			</layoutCol>

			<layoutCol(align)>
				<title("", font) public id="time" />
				<text text="Cumulated_6.2" />
			</layoutCol>
		</layoutLine>

	</container>;



	public function new(align:h2d.Flow.FlowAlign, ?parent) {
		super(parent);
		initComponent();

	}

}

