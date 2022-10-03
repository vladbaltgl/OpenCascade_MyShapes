#include"Viewer.h"
#include<BRepPrimAPI_MakeCone.hxx>
#include<Font_FTFont.hxx>
//OCC
#include<AIS_ColorScale.hxx>
#include<BRepPrimAPI_MakeBox.hxx>
#include<BRepTools.hxx>
#include<Graphic3d_Text.hxx>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<BRepBuilderAPI_Transform.hxx>
#include<BRepBuilderAPI_MakeWire.hxx>
#include<BRepPrimAPI_MakePrism.hxx>
#include<BRepFilletAPI_MakeFillet.hxx>
#include<BRepBuilderAPI_MakeFace.hxx>
#include<BRepPrimAPI_MakeCylinder.hxx>
#include<TopExp_Explorer.hxx>
#include<BRepAlgoAPI_Fuse.hxx>
#include<BRepOffsetAPI_MakeThickSolid.hxx>
#include<Standard_Handle.hxx>
#include<GC_MakeSegment.hxx>
#include<GC_MakeArcOfCircle.hxx>
#include<Standard_Type.hxx>
#include<Geom_CylindricalSurface.hxx>
#include<Geom2d_TrimmedCurve.hxx>
#include<GCE2d_MakeSegment.hxx>
#include<Geom2d_Ellipse.hxx>
#include<BRepOffsetAPI_ThruSections.hxx>
#include<BRepLib.hxx>
#include<gp_Pnt.hxx>
#include<Geom_Plane.hxx>
#include<BRepBuilderAPI_Sewing.hxx>
#include<Geom_ConicalSurface.hxx>
#include <gce_MakeCone.hxx>
#include<AIS_ColoredShape.hxx>
#include<iostream>
#include<Graphic3d_Group.hxx>
#include<Graphic3d_Vertex.hxx>
#include<Font_BRepFont.hxx>
#include<Font_BRepTextBuilder.hxx>
#include<PrsDim_AngleDimension.hxx>
#include<StdPrs_WFShape.hxx>
#include<Prs3d_BndBox.hxx>
#include<BRepBndLib.hxx>
#include<GeomAPI_PointsToBSpline.hxx>
#include<BRepOffsetAPI_MakeOffset.hxx>
#include <math.h>
#include <stdio.h> 
#include<GeomAPI_ProjectPointOnCurve.hxx>
#include<AIS_Shape.hxx>
#include<BRepPrimAPI_MakeSweep.hxx>
#include<ShapeFix_Face.hxx>
#include <gp_Cylinder.hxx>
#include<BRepBuilderAPI_MakeVertex.hxx>
#include<GeomAPI_IntSS.hxx>
#include<BRepFill.hxx>
#include<BRepBuilderAPI_Sewing.hxx>
#include<XCAFDoc_DocumentTool.hxx>
#include<StdPrs_ShadedShape.hxx>
#include<BRepBuilderAPI_MakePolygon.hxx>
#include<PrsDim_DiameterDimension.hxx>
#include<vector>
using namespace std;
#include<AIS_Shape.hxx>
#include<AIS_AnimationObject.hxx>
#include<AIS_Animation.hxx>
#include<BRepPrimAPI_MakeRevol.hxx>
#include <Prs3d_Arrow.hxx>

#include <AIS_TextLabel.hxx>




using namespace std;

const double PI = 3.1415926536;
//direction
enum direction { x, y, z };


//complete 2 bracket
TopoDS_Shape bracket(double centr_x1, double centr_y1, double centr_x2, double centr_y2, double radius_1, double radius_2) {



	//---------------------angle calculation--------------------------
	double alpha_plus1, alpha_plus2;

	double at_1, at_2;
	double arcosinus1, arcosinus2;
	//alpha_plus
	at_1 = atan2((centr_y2 - centr_y1), (centr_x2 - centr_x1));
	at_2 = atan2((centr_y1 - centr_y2), (centr_x1 - centr_x2));
	arcosinus1 = acos((radius_1 - radius_2) / abs(sqrt(pow((centr_x2 - centr_x1), 2) + pow((centr_y2 - centr_y1), 2))));
	arcosinus2 = acos((radius_2 - radius_1) / abs(sqrt(pow((centr_x1 - centr_x2), 2) + pow((centr_y1 - centr_y2), 2))));
	alpha_plus1 = at_1 + arcosinus1;
	alpha_plus2 = at_2 + arcosinus2;

	//---------------------angle calculation_finish-------------------









	//-------------------calculation of tangent points-----------------

	double tangent_point_21_x, tangent_point_21_y, tangent_point_2_x, tangent_point_2_y, tangent_point_41_x, tangent_point_41_y, tangent_point_4_x, tangent_point_4_y;

	tangent_point_21_x = centr_x1 + radius_1 * cos(alpha_plus2);//true
	tangent_point_21_y = centr_y1 + radius_1 * sin(alpha_plus2);



	tangent_point_2_x = centr_x1 + radius_1 * cos(alpha_plus1);//true
	tangent_point_2_y = centr_y1 + radius_1 * sin(alpha_plus1);



	tangent_point_41_x = centr_x2 + radius_2 * cos(alpha_plus2);//true
	tangent_point_41_y = centr_y2 + radius_2 * sin(alpha_plus2);


	tangent_point_4_x = centr_x2 + radius_2 * cos(alpha_plus1);//true
	tangent_point_4_y = centr_y2 + radius_2 * sin(alpha_plus1);


	//-------------------calculation of tangent points_finish-----------------





	//------------------do points---------------------------------------------

	//first circle
	gp_Pnt tp_21(tangent_point_21_x, tangent_point_21_y, 0);
	gp_Pnt tp_2(tangent_point_2_x, tangent_point_2_y, 0);


	//second circle
	gp_Pnt tp_41(tangent_point_41_x, tangent_point_41_y, 0);
	gp_Pnt tp_4(tangent_point_4_x, tangent_point_4_y, 0);


	//------------------do points_finish---------------------------------------------



//do tangents segments
	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(tp_21, tp_41);
	Handle(Geom_TrimmedCurve) aSegment2 = GC_MakeSegment(tp_2, tp_4);

	//do tangents edges
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(aSegment2);

	//do arc_1
	gp_Circ gpCirc_1;
	gpCirc_1.SetRadius(radius_1);
	gp_Pnt circleCenter_1(centr_x1, centr_y1, 0);
	gpCirc_1.SetLocation(circleCenter_1);
	Handle(Geom_TrimmedCurve) geometricArc_1 = GC_MakeArcOfCircle(gpCirc_1, tp_2, tp_21, true);
	TopoDS_Edge arc_edge_1 = BRepBuilderAPI_MakeEdge(geometricArc_1);


	//do arc_2
	gp_Circ gpCirc_2;
	gpCirc_2.SetRadius(radius_2);
	gp_Pnt circleCenter_2(centr_x2, centr_y2, 0);
	gpCirc_2.SetLocation(circleCenter_2);
	Handle(Geom_TrimmedCurve) geometricArc_2 = GC_MakeArcOfCircle(gpCirc_2, tp_41, tp_4, true);
	TopoDS_Edge arc_edge_2 = BRepBuilderAPI_MakeEdge(geometricArc_2);



	//------------------do segments_finish--------------------------------------------------




	//do shape

	gp_Vec aPrismVec(0, 0, 2);


	Handle(Geom_TrimmedCurve) aSegment3 = GC_MakeSegment(tp_2, tp_21);
	Handle(Geom_TrimmedCurve) aSegment4 = GC_MakeSegment(tp_41, tp_4);

	TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge(aSegment3);
	TopoDS_Edge anEdge4 = BRepBuilderAPI_MakeEdge(aSegment4);


	BRepBuilderAPI_MakeWire myWireTest(arc_edge_1, anEdge1, anEdge2, arc_edge_2);

	TopoDS_Shape myBodyTest = BRepPrimAPI_MakePrism(myWireTest, aPrismVec);



	return  myBodyTest;
}

//complete 3 bracket
TopoDS_Shape bracket(double centr_x1, double centr_y1, double centr_x2, double centr_y2, double centr_x3, double centr_y3, double radius_1, double radius_2, double radius_3) {



	//---------------------angle calculation--------------------------
	double alpha_plus1, alpha_plus2, alpha_plus3;

	double at_1, at_2, at_3;
	double arcosinus1, arcosinus2, arcosinus3;
	//alpha_plus
	at_1 = atan2((centr_y2 - centr_y1), (centr_x2 - centr_x1));
	at_2 = atan2((centr_y3 - centr_y2), (centr_x3 - centr_x2));
	at_3 = atan2((centr_y1 - centr_y3), (centr_x1 - centr_x3));
	//at_2 = atan2((centr_y1 - centr_y2), (centr_x1 - centr_x2));
	arcosinus1 = acos((radius_1 - radius_2) / abs(sqrt(pow((centr_x2 - centr_x1), 2) + pow((centr_y2 - centr_y1), 2))));
	arcosinus2 = acos((radius_2 - radius_3) / abs(sqrt(pow((centr_x3 - centr_x2), 2) + pow((centr_y3 - centr_y2), 2))));
	arcosinus3 = acos((radius_3 - radius_1) / abs(sqrt(pow((centr_x1 - centr_x3), 2) + pow((centr_y1 - centr_y3), 2))));

	alpha_plus1 = at_1 + arcosinus1;
	alpha_plus2 = at_2 + arcosinus2;
	alpha_plus3 = at_3 + arcosinus3;

	//---------------------angle calculation_finish-------------------


	//-------------------calculation of tangent points-----------------

	double tangent_point_21_x, tangent_point_21_y, tangent_point_2_x, tangent_point_2_y, tangent_point_41_x, tangent_point_41_y, tangent_point_4_x, tangent_point_4_y, tangent_point_81_x, tangent_point_81_y, tangent_point_8_x, tangent_point_8_y;



	tangent_point_2_x = centr_x1 + radius_1 * cos(alpha_plus1);
	tangent_point_2_y = centr_y1 + radius_1 * sin(alpha_plus1);

	tangent_point_4_x = centr_x2 + radius_2 * cos(alpha_plus1);
	tangent_point_4_y = centr_y2 + radius_2 * sin(alpha_plus1);

	tangent_point_41_x = centr_x2 + radius_2 * cos(alpha_plus2);
	tangent_point_41_y = centr_y2 + radius_2 * sin(alpha_plus2);

	tangent_point_8_x = centr_x3 + radius_3 * cos(alpha_plus2);
	tangent_point_8_y = centr_y3 + radius_3 * sin(alpha_plus2);





	tangent_point_81_x = centr_x3 + radius_3 * cos(alpha_plus3);
	tangent_point_81_y = centr_y3 + radius_3 * sin(alpha_plus3);

	tangent_point_21_x = centr_x1 + radius_1 * cos(alpha_plus3);
	tangent_point_21_y = centr_y1 + radius_1 * sin(alpha_plus3);



	//-------------------calculation of tangent points_finish-----------------




	//------------------do points---------------------------------------------

	//first circle
	gp_Pnt tp_21(tangent_point_21_x, tangent_point_21_y, 0);
	gp_Pnt tp_2(tangent_point_2_x, tangent_point_2_y, 0);


	//second circle
	gp_Pnt tp_81(tangent_point_81_x, tangent_point_81_y, 0);
	gp_Pnt tp_8(tangent_point_8_x, tangent_point_8_y, 0);
	// third circle
	gp_Pnt tp_41(tangent_point_41_x, tangent_point_41_y, 0);
	gp_Pnt tp_4(tangent_point_4_x, tangent_point_4_y, 0);



	//------------------do points_finish---------------------------------------------




	//------------------do segments--------------------------------------------------


	//do tangents segments
	Handle(Geom_TrimmedCurve) aSegment3 = GC_MakeSegment(tp_2, tp_4);
	Handle(Geom_TrimmedCurve) aSegment2 = GC_MakeSegment(tp_41, tp_8);
	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(tp_81, tp_21);



	//do tangents edges
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(aSegment2);
	TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge(aSegment3);

	//do arc_1
	gp_Circ gpCirc_1;
	gpCirc_1.SetRadius(radius_1);
	gp_Pnt circleCenter_1(centr_x1, centr_y1, 0);
	gpCirc_1.SetLocation(circleCenter_1);
	Handle(Geom_TrimmedCurve) geometricArc_1 = GC_MakeArcOfCircle(gpCirc_1, tp_2, tp_21, true);
	TopoDS_Edge arc_edge_1 = BRepBuilderAPI_MakeEdge(geometricArc_1);


	//do arc_2
	gp_Circ gpCirc_2;
	gpCirc_2.SetRadius(radius_2);
	gp_Pnt circleCenter_2(centr_x2, centr_y2, 0);
	gpCirc_2.SetLocation(circleCenter_2);
	Handle(Geom_TrimmedCurve) geometricArc_2 = GC_MakeArcOfCircle(gpCirc_2, tp_41, tp_4, true);
	TopoDS_Edge arc_edge_2 = BRepBuilderAPI_MakeEdge(geometricArc_2);


	//do arc_3
	gp_Circ gpCirc_3;
	gpCirc_3.SetRadius(radius_3);
	gp_Pnt circleCenter_3(centr_x3, centr_y3, 0);
	gpCirc_3.SetLocation(circleCenter_3);
	Handle(Geom_TrimmedCurve) geometricArc_3 = GC_MakeArcOfCircle(gpCirc_3, tp_81, tp_8, true);
	TopoDS_Edge arc_edge_3 = BRepBuilderAPI_MakeEdge(geometricArc_3);


	//------------------do segments_finish--------------------------------------------------




	//-----------------do shape-------------------------------------------------------------

	gp_Vec aPrismVec(0, 0, 2);
	BRepBuilderAPI_MakeWire myWireTest(anEdge3, arc_edge_2, anEdge2, arc_edge_1);
	myWireTest.Add(anEdge1);
	myWireTest.Add(arc_edge_3);
	TopoDS_Shape myBodyTest = BRepPrimAPI_MakePrism(myWireTest, aPrismVec);
	//-----------------do shape_finish-------------------------------------------------------------




	return  myBodyTest;
}

//complete 4 bracket
TopoDS_Shape bracket(double centr_x1, double centr_y1, double centr_x2, double centr_y2, double centr_x3, double centr_y3, double centr_x4, double centr_y4, double radius_1, double radius_2, double radius_3, double radius_4) {



	//---------------------angle calculation--------------------------
	double alpha_plus1, alpha_plus2, alpha_plus3, alpha_plus4;

	double at_1, at_2, at_3, at_4;
	double arcosinus1, arcosinus2, arcosinus3, arcosinus4;
	//alpha_plus


	at_1 = atan2((centr_y1 - centr_y2), (centr_x1 - centr_x2));
	at_2 = atan2((centr_y2 - centr_y3), (centr_x2 - centr_x3));
	at_3 = atan2((centr_y3 - centr_y4), (centr_x3 - centr_x4));
	at_4 = atan2((centr_y4 - centr_y1), (centr_x4 - centr_x1));



	arcosinus1 = acos((radius_2 - radius_1) / (sqrt(pow((centr_x1 - centr_x2), 2) + pow((centr_y1 - centr_y2), 2))));
	arcosinus2 = acos((radius_3 - radius_2) / (sqrt(pow((centr_x2 - centr_x3), 2) + pow((centr_y2 - centr_y3), 2))));
	arcosinus3 = acos((radius_4 - radius_3) / (sqrt(pow((centr_x3 - centr_x4), 2) + pow((centr_y3 - centr_y4), 2))));
	arcosinus4 = acos((radius_1 - radius_4) / (sqrt(pow((centr_x4 - centr_x1), 2) + pow((centr_y4 - centr_y1), 2))));


	alpha_plus1 = at_1 + arcosinus1;
	alpha_plus2 = at_2 + arcosinus2;
	alpha_plus3 = at_3 + arcosinus3;
	alpha_plus4 = at_4 + arcosinus4;

	//---------------------angle calculation_finish-------------------





	//-------------------calculation of tangent points-----------------

	double tangent_point_21_x, tangent_point_21_y, tangent_point_2_x, tangent_point_2_y, tangent_point_41_x, tangent_point_41_y, tangent_point_4_x, tangent_point_4_y, tangent_point_81_x, tangent_point_81_y, tangent_point_8_x, tangent_point_8_y, tangent_point_161_x, tangent_point_161_y, tangent_point_16_x, tangent_point_16_y;



	tangent_point_2_x = centr_x1 + radius_1 * cos(alpha_plus1);
	tangent_point_2_y = centr_y1 + radius_1 * sin(alpha_plus1);

	tangent_point_4_x = centr_x2 + radius_2 * cos(alpha_plus1);
	tangent_point_4_y = centr_y2 + radius_2 * sin(alpha_plus1);

	tangent_point_41_x = centr_x2 + radius_2 * cos(alpha_plus2);
	tangent_point_41_y = centr_y2 + radius_2 * sin(alpha_plus2);

	tangent_point_8_x = centr_x3 + radius_3 * cos(alpha_plus2);
	tangent_point_8_y = centr_y3 + radius_3 * sin(alpha_plus2);


	tangent_point_81_x = centr_x3 + radius_3 * cos(alpha_plus3);
	tangent_point_81_y = centr_y3 + radius_3 * sin(alpha_plus3);



	tangent_point_16_x = centr_x4 + radius_4 * cos(alpha_plus3);
	tangent_point_16_y = centr_y4 + radius_4 * sin(alpha_plus3);



	tangent_point_161_x = centr_x4 + radius_4 * cos(alpha_plus4);
	tangent_point_161_y = centr_y4 + radius_4 * sin(alpha_plus4);


	tangent_point_21_x = centr_x1 + radius_1 * cos(alpha_plus4);
	tangent_point_21_y = centr_y1 + radius_1 * sin(alpha_plus4);


	//-------------------calculation of tangent points_finish-----------------




	//------------------do points---------------------------------------------

	//first circle
	gp_Pnt tp_21(tangent_point_21_x, tangent_point_21_y, 0);
	gp_Pnt tp_2(tangent_point_2_x, tangent_point_2_y, 0);


	//second circle
	gp_Pnt tp_81(tangent_point_81_x, tangent_point_81_y, 0);
	gp_Pnt tp_8(tangent_point_8_x, tangent_point_8_y, 0);
	// third circle
	gp_Pnt tp_41(tangent_point_41_x, tangent_point_41_y, 0);
	gp_Pnt tp_4(tangent_point_4_x, tangent_point_4_y, 0);

	//fourh circle
	gp_Pnt tp_161(tangent_point_161_x, tangent_point_161_y, 0);
	gp_Pnt tp_16(tangent_point_16_x, tangent_point_16_y, 0);




	//do segments-

	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(tp_2, tp_4);
	Handle(Geom_TrimmedCurve) aSegment2 = GC_MakeSegment(tp_41, tp_8);
	Handle(Geom_TrimmedCurve) aSegment3 = GC_MakeSegment(tp_16, tp_81);
	Handle(Geom_TrimmedCurve) aSegment4 = GC_MakeSegment(tp_161, tp_21);




	//do tangents edges
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(aSegment2);
	TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge(aSegment3);
	TopoDS_Edge anEdge4 = BRepBuilderAPI_MakeEdge(aSegment4);


	//do arc_1
	gp_Circ gpCirc_1;
	gpCirc_1.SetRadius(radius_1);
	gp_Pnt circleCenter_1(centr_x1, centr_y1, 0);
	gpCirc_1.SetLocation(circleCenter_1);
	Handle(Geom_TrimmedCurve) geometricArc_1 = GC_MakeArcOfCircle(gpCirc_1, tp_21, tp_2, true);
	TopoDS_Edge arc_edge_1 = BRepBuilderAPI_MakeEdge(geometricArc_1);


	//do arc_2
	gp_Circ gpCirc_2;
	gpCirc_2.SetRadius(radius_2);
	gp_Pnt circleCenter_2(centr_x2, centr_y2, 0);
	gpCirc_2.SetLocation(circleCenter_2);
	Handle(Geom_TrimmedCurve) geometricArc_2 = GC_MakeArcOfCircle(gpCirc_2, tp_4, tp_41, true);
	TopoDS_Edge arc_edge_2 = BRepBuilderAPI_MakeEdge(geometricArc_2);


	//do arc_3
	gp_Circ gpCirc_3;
	gpCirc_3.SetRadius(radius_3);
	gp_Pnt circleCenter_3(centr_x3, centr_y3, 0);
	gpCirc_3.SetLocation(circleCenter_3);
	Handle(Geom_TrimmedCurve) geometricArc_3 = GC_MakeArcOfCircle(gpCirc_3, tp_8, tp_81, true);
	TopoDS_Edge arc_edge_3 = BRepBuilderAPI_MakeEdge(geometricArc_3);

	//do arc_4
	gp_Circ gpCirc_4;
	gpCirc_4.SetRadius(radius_4);
	gp_Pnt circleCenter_4(centr_x4, centr_y4, 0);
	gpCirc_4.SetLocation(circleCenter_4);
	Handle(Geom_TrimmedCurve) geometricArc_4 = GC_MakeArcOfCircle(gpCirc_4, tp_16, tp_161, true);
	TopoDS_Edge arc_edge_4 = BRepBuilderAPI_MakeEdge(geometricArc_4);

	//do shape
	gp_Vec aPrismVec(0, 0, 4);

	BRepBuilderAPI_MakeWire myWireTest(anEdge4, arc_edge_4, anEdge3);


	myWireTest.Add(arc_edge_3);

	myWireTest.Add(anEdge2);
	myWireTest.Add(arc_edge_2);

	myWireTest.Add(anEdge1);
	myWireTest.Add(arc_edge_1);

	TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(myWireTest);

	TopoDS_Shape myBody = BRepPrimAPI_MakePrism(myFaceProfile, aPrismVec);


	return  myBody;
}

//arrow
TopoDS_Shape arrow(double arow_len, double conus_len, double conus_radius, double cylindr_radius, double cylindr_x, double cylindr_y, double cylindr_z)
{
	//build conus
	gp_Dir arow_dir;

	arow_dir = gp::DZ();

	//build cylindr
	gp_Pnt cylindr_Location(cylindr_x, cylindr_y, cylindr_z);
	gp_Ax2 cylindr_xyz(cylindr_Location, arow_dir);
	//draw cylindr
	BRepPrimAPI_MakeCylinder MKCylinder(cylindr_xyz, cylindr_radius, arow_len - conus_len);
	TopoDS_Shape myCylindr = MKCylinder.Shape();


	gp_Pnt conus_Location;

	conus_Location.SetCoord(cylindr_x, cylindr_y, cylindr_z + (arow_len - conus_len));

	gp_Ax2 conus_xyz(conus_Location, arow_dir);
	//draw conus
	BRepPrimAPI_MakeCone MKCone(conus_xyz, conus_radius, 0, conus_len);
	TopoDS_Shape myConus = MKCone.Shape();



	//drow arow
	TopoDS_Shape arow = BRepAlgoAPI_Fuse(myCylindr, myConus);

	return arow;

}



//circular arrow
TopoDS_Shape  arc_arrow(double center_x, double center_y, double h1, double  arc_radius, double conus_radius, double conus_len, double arow_len)
{


	TopoDS_Shape  shape_arc_2 = arrow(arow_len, conus_len, conus_radius, h1, center_x, center_y, -1 * ((arow_len - conus_len) / 2) + h1 / 2);


	arc_radius += h1;
	gp_Circ gpCirc_arc_1;
	gpCirc_arc_1.SetRadius(arc_radius);
	gp_Pnt circle_first1(center_x, center_y, 0);
	gpCirc_arc_1.SetLocation(circle_first1);
	Handle(Geom_TrimmedCurve) geometricArc_arc_1 = GC_MakeArcOfCircle(gpCirc_arc_1, 3 * PI / 2, PI, true);

	TopoDS_Edge arc_edge_1 = BRepBuilderAPI_MakeEdge(geometricArc_arc_1);




	gp_Circ gpCirc_arc_2;
	gpCirc_arc_2.SetRadius(arc_radius + h1);
	gp_Pnt circle_first2(center_x, center_y, 0);
	gpCirc_arc_2.SetLocation(circle_first2);
	Handle(Geom_TrimmedCurve) geometricArc_arc2 = GC_MakeArcOfCircle(gpCirc_arc_2, 3 * PI / 2, PI, true);

	TopoDS_Edge arc_edge_2 = BRepBuilderAPI_MakeEdge(geometricArc_arc2);


	gp_Vec aPrismVec(0, 0, h1);


	gp_Pnt gpc1(center_x, center_y - arc_radius, 0);
	gp_Pnt gpc2(center_x, center_y - arc_radius - h1, 0);
	gp_Pnt gpc3(center_x - arc_radius, center_y, 0);
	gp_Pnt gpc4(center_x - arc_radius - h1, center_y, 0);



	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(gpc1, gpc2);
	Handle(Geom_TrimmedCurve) aSegment2 = GC_MakeSegment(gpc3, gpc4);




	//do tangents edges
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(aSegment2);

	BRepBuilderAPI_MakeWire myWireTest1(anEdge1, arc_edge_1, arc_edge_2, anEdge2);


	//build conus
	gp_Dir arow_dir;
	gp_Pnt conus_Location;

	arow_dir = -gp::DY();

	//	arow_dir = gp::DX();

	conus_Location.SetCoord(center_x - arc_radius - h1 / 2, 0, h1 / 2);
	gp_Ax2 conus_xyz(conus_Location, arow_dir);

	//draw conus
	BRepPrimAPI_MakeCone MKCone(conus_xyz, conus_radius, 0, conus_len);
	TopoDS_Shape myConus = MKCone.Shape();



	

	//draw conus



	TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(myWireTest1);


	TopoDS_Shape myBodyTest = BRepPrimAPI_MakePrism(myFaceProfile, aPrismVec).Shape();


	TopoDS_Shape shape_arc_1 = BRepAlgoAPI_Fuse(myBodyTest, myConus);



	TopoDS_Shape myBody = BRepAlgoAPI_Fuse(shape_arc_1, shape_arc_2);


	return myBody;
}




//polygon point set
vector<gp_Pnt> polygon_vec_points_test() {
	vector<gp_Pnt> vector_list;
	vector_list.push_back(gp_Pnt(0, 0, 0));
	vector_list.push_back(gp_Pnt(10, -10, 0));
	vector_list.push_back(gp_Pnt(20, 0, 0));
	vector_list.push_back(gp_Pnt(20, 20, 0));
	vector_list.push_back(gp_Pnt(0, 20, 0));
	return vector_list;

}
//polygon
TopoDS_Shape polygon(vector<gp_Pnt>& pvec, double h) {

	vector<Handle(Geom_TrimmedCurve)>aSegments;
	vector<TopoDS_Edge>anEdges;
	for (int i = 0; i < pvec.size(); ++i) {
		if (i == pvec.size() - 1) {
			Handle(Geom_TrimmedCurve) aSegment = GC_MakeSegment(pvec[i], pvec[0]);
			aSegments.push_back(aSegment);
			break;
		}

		Handle(Geom_TrimmedCurve) aSegment = GC_MakeSegment(pvec[i], pvec[i + 1]);
		aSegments.push_back(aSegment);
	}

	for (int i = 0; i < aSegments.size(); ++i) {
		TopoDS_Edge anEdge = BRepBuilderAPI_MakeEdge(aSegments[i]);
		anEdges.push_back(anEdge);
	}

	BRepBuilderAPI_MakeWire myWireTest;
	for (int i = 0; i < anEdges.size(); ++i) {
		myWireTest.Add(anEdges[i]);
	}

	gp_Vec aPrismVec(0, 0, h);
	TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(myWireTest);

	TopoDS_Shape myBody = BRepPrimAPI_MakePrism(myFaceProfile, aPrismVec);

	return myBody;
}




//worm gear
TopoDS_Shape warm_broadcast(double center_x1, double center_y1, double radius_1, double radius_2, double h1, double h2, double b1) {


	double	arc_radius = radius_1;
	gp_Circ gpCirc_arc_1;
	gpCirc_arc_1.SetRadius(arc_radius);
	gp_Pnt circle_first1(center_x1, center_y1, 0);
	gpCirc_arc_1.SetLocation(circle_first1);
	Handle(Geom_TrimmedCurve) geometricArc_arc_1 = GC_MakeArcOfCircle(gpCirc_arc_1, 360 * PI / 180, 0, true);

	TopoDS_Edge arc_edge_1 = BRepBuilderAPI_MakeEdge(geometricArc_arc_1);
	BRepBuilderAPI_MakeWire myWireTest(arc_edge_1);





	gp_Vec aPrismVec(0, 0, h1);
	TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(myWireTest);

	TopoDS_Shape myBody = BRepPrimAPI_MakePrism(myFaceProfile, aPrismVec);


	//draw cylindr1
	gp_Dir gear_dir = gp::DX();

	gp_Pnt cylindr_Location2(center_x1 - (h2 / 2), center_y1 - radius_1 - radius_2 + b1, h1 / 2);
	gp_Ax2 cylindr_xyz_2(cylindr_Location2, gear_dir);


	BRepPrimAPI_MakeCylinder MKCylinder2(cylindr_xyz_2, radius_2 + b1, h2);
	TopoDS_Shape myCylindr2 = MKCylinder2.Shape();



	TopoDS_Shape gear = BRepAlgoAPI_Fuse(myBody, myCylindr2);





	return gear;

}


//bevel gear
TopoDS_Shape conus_broadcast(double center_gear1_x, double center_gear1_y, double r1, double h1, double alpha, double b)
{




	//первая точка вектор1

	gp_Pnt pepe1_1(center_gear1_x, center_gear1_y, 0);
	gp_Pnt pepe1_2(center_gear1_x, center_gear1_y + h1, 0);

	gp_Vec gek1(pepe1_1, pepe1_2);
	gp_Pnt gp_gear1_center1(center_gear1_x, center_gear1_y, 0);
	gp_Dir gear1_dir = gek1;

	gp_Ax2 ax2_gear1_center(gp_gear1_center1, gear1_dir);



	//вычисления


	double gypotenusa = sqrt(pow(h1, 2) + pow(r1, 2));
	double betta_1 = atan(h1 / r1);
	double chtoto = h1 / r1;
	double alpha1 = PI / 2 - betta_1;
	double alpha2 = alpha * PI / 180 - alpha1;
	double r2 = gypotenusa * sin(alpha2);
	double h2 = gypotenusa * cos(alpha2);
	double betta_2 = PI / 2 - alpha2;
	double angle_dx = PI - betta_1 - betta_2;
	double kat_dy = r2 * sin(angle_dx);
	double kat_dx = r2 * cos(angle_dx);


	//ищем срез конуса
	double kef = gypotenusa / (gypotenusa - b);
	double h1_shtrih = h1 - (h1 / kef);
	double h2_shtrih = h2 - (h2 / kef);
	double r1_shtrih = (r1 / kef);
	double r2_shtrih = (r2 / kef);

	//вектор  2
	gp_Pnt pepe2_1(center_gear1_x + r1 + kat_dx, center_gear1_y + kat_dy, 0);
	gp_Pnt pepe2_2(center_gear1_x, center_gear1_y + h1, 0);

	gp_Vec gek2(pepe2_1, pepe2_2);


	//вторая точка
	gp_Dir gear2_dir(gek2);
	//gp_Dir gear2_dir;
	//gear2_dir = -gp::DX();
	gp_Pnt gp_gear2_center(center_gear1_x + r1 + kat_dx, center_gear1_y + kat_dy, 0);
	gp_Ax2 ax2_gear2_center(gp_gear2_center, gear2_dir);





	//построения
	BRepPrimAPI_MakeCone gear1(ax2_gear1_center, r1, r1_shtrih, h1_shtrih);
	BRepPrimAPI_MakeCone gear2(ax2_gear2_center, r2, r2_shtrih, h2_shtrih);
	TopoDS_Shape myGear = BRepAlgoAPI_Fuse(gear1, gear2);



	//Standard_EXPORT BRepPrimAPI_MakeCone(const gp_Ax2& Axes, const Standard_Real R1, const Standard_Real R2, const Standard_Real H);

	//draw conus


	return myGear;
}

//spur gear
TopoDS_Shape cylindr_broadcast(double center_x1, double center_y1, double center_x2, double center_y2, double radius_1, double radius_2, double h1, double h2) {

	gp_Dir arow_dir = gp::DX();


	//draw cylindr1
	gp_Pnt cylindr_Location1(center_x1, center_y1, 0);
	gp_Ax2 cylindr_xyz_1(cylindr_Location1, arow_dir);

	BRepPrimAPI_MakeCylinder MKCylinder1(cylindr_xyz_1, radius_1, h1);
	TopoDS_Shape myCylindr1 = MKCylinder1.Shape();



	//draw cylindr2

	gp_Pnt cylindr_Location2(center_x2, center_y2, 0);
	gp_Ax2 cylindr_xyz_2(cylindr_Location2, arow_dir);


	BRepPrimAPI_MakeCylinder MKCylinder2(cylindr_xyz_2, radius_2, h2);
	TopoDS_Shape myCylindr2 = MKCylinder2.Shape();



	TopoDS_Shape gear = BRepAlgoAPI_Fuse(myCylindr1, myCylindr2);


	return gear;

}



//car
TopoDS_Shape makeCar(int koleso1_x, int koleso1_y, int koleso2_x, int koleso2_y, double radius, double height, double height1, double width) {

	const double kef_radius = 2.5;

	gp_Pnt koleso1(koleso1_x, koleso1_y, 0);

	gp_Pnt koleso2(koleso2_x, koleso2_y, 0);

	double base = sqrt(pow(koleso2_x - koleso1_x, 2) + pow(koleso2_y - koleso1_y, 2));

	double length = base + (kef_radius * radius) * 2;


	double length_up = length * 2 / 3;

	double center_length_x = length / 2;






	//base
	gp_Pnt left_p(koleso1_x - kef_radius * radius, koleso1_y, 0);
	gp_Pnt right_p(koleso2_x + kef_radius * radius, koleso1_y, 0);




	gp_Pnt left_up_p(koleso1_x - kef_radius * radius + center_length_x - (length_up / 2), koleso1_y + height1, 0);
	gp_Pnt right_up_p(koleso2_x + kef_radius * radius - center_length_x + (length_up / 2), koleso1_y + height1, 0);









	Handle(Geom_TrimmedCurve) aSegment_base = GC_MakeSegment(left_p, right_p);

	Handle(Geom_TrimmedCurve) aSegment_up_base = GC_MakeSegment(left_up_p, right_up_p);

	Handle(Geom_TrimmedCurve) aSegment_tunc = GC_MakeSegment(left_p, left_up_p);

	Handle(Geom_TrimmedCurve) aSegment_bam = GC_MakeSegment(right_p, right_up_p);

	TopoDS_Edge anEdge_base = BRepBuilderAPI_MakeEdge(aSegment_base);

	TopoDS_Edge anEdge_up_base = BRepBuilderAPI_MakeEdge(aSegment_up_base);

	TopoDS_Edge anEdge_trunc = BRepBuilderAPI_MakeEdge(aSegment_tunc);

	TopoDS_Edge anEdge_bam = BRepBuilderAPI_MakeEdge(aSegment_bam);

	BRepBuilderAPI_MakeWire myWireTest(anEdge_base, anEdge_trunc, anEdge_up_base, anEdge_bam);

	TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(myWireTest);

	gp_Vec aPrismVec(0, 0, width);


	TopoDS_Shape myBody_base = BRepPrimAPI_MakePrism(myFaceProfile, aPrismVec);

	//roof



	gp_Pnt center_roof(koleso1_x + (base / 2), koleso1_y + height1, 0);

	double roof_length = length * 2 / 5;

	double raschet_centra = koleso1_x + (base / 2);

	double up_roof_length = roof_length * 4 / 5;

	double height_roof = height - height1;

	gp_Pnt left_up_roof(koleso1_x - kef_radius * radius + length / 2 - (up_roof_length / 2), koleso1_y + height1 + height_roof, 0);

	gp_Pnt right_up_roof(koleso1_x - kef_radius * radius + length / 2 + (up_roof_length / 2), koleso1_y + height1 + height_roof, 0);


	gp_Pnt left_roof(raschet_centra - (roof_length / 2), koleso1_y + height1, 0);

	gp_Pnt right_roof(raschet_centra + (roof_length / 2), koleso1_y + height1, 0);

	Handle(Geom_TrimmedCurve) aSegment_base_roof = GC_MakeSegment(left_roof, right_roof);

	Handle(Geom_TrimmedCurve) aSegment_up_base_roof = GC_MakeSegment(left_up_roof, right_up_roof);

	Handle(Geom_TrimmedCurve) aSegment_tunc_roof = GC_MakeSegment(left_roof, left_up_roof);

	Handle(Geom_TrimmedCurve) aSegment_bam_roof = GC_MakeSegment(right_roof, right_up_roof);

	TopoDS_Edge anEdge_base_roof = BRepBuilderAPI_MakeEdge(aSegment_base_roof);

	TopoDS_Edge anEdge_up_base_roof = BRepBuilderAPI_MakeEdge(aSegment_up_base_roof);

	TopoDS_Edge anEdge_trunc_roof = BRepBuilderAPI_MakeEdge(aSegment_tunc_roof);

	TopoDS_Edge anEdge_bam_roof = BRepBuilderAPI_MakeEdge(aSegment_bam_roof);


	BRepBuilderAPI_MakeWire myWireTest2(anEdge_base_roof, anEdge_trunc_roof, anEdge_up_base_roof, anEdge_bam_roof);

	TopoDS_Face myFaceProfile2 = BRepBuilderAPI_MakeFace(myWireTest2);

	TopoDS_Shape myBody_roof = BRepPrimAPI_MakePrism(myFaceProfile2, aPrismVec);


	TopoDS_Shape superCar = BRepAlgoAPI_Fuse(myBody_base, myBody_roof);





	return superCar;
}

//trailer
TopoDS_Shape makeCar_with_trailer(int koleso1_x, int koleso1_y, int koleso2_x, int koleso2_y, double radius, double height, double height1, double width, double lenght_trailer, double height_trailer) {
	gp_Pnt koleso1(koleso1_x, koleso1_y, 0);
	gp_Pnt koleso2(koleso2_x, koleso2_y, 0);

	const double kef_radius = 2.5;

	double base = sqrt(pow(koleso2_x - koleso1_x, 2) + pow(koleso2_y - koleso1_y, 2));
	double length = base + (kef_radius * radius) * 2;
	double length_up = length * 1 / 3;

	//base
	gp_Pnt left_p(koleso1_x - kef_radius * radius, koleso1_y, 0);
	gp_Pnt right_p(koleso2_x + kef_radius * radius, koleso1_y, 0);



	gp_Pnt left_up_p(koleso1_x - kef_radius * radius, koleso1_y + height1, 0);
	gp_Pnt right_up_p(koleso2_x + kef_radius * radius, koleso1_y + height1, 0);

	Handle(Geom_TrimmedCurve) aSegment_base = GC_MakeSegment(left_p, right_p);

	Handle(Geom_TrimmedCurve) aSegment_up_base = GC_MakeSegment(left_up_p, right_up_p);

	Handle(Geom_TrimmedCurve) aSegment_tunc = GC_MakeSegment(left_p, left_up_p);

	Handle(Geom_TrimmedCurve) aSegment_bam = GC_MakeSegment(right_p, right_up_p);

	TopoDS_Edge anEdge_base = BRepBuilderAPI_MakeEdge(aSegment_base);

	TopoDS_Edge anEdge_up_base = BRepBuilderAPI_MakeEdge(aSegment_up_base);

	TopoDS_Edge anEdge_trunc = BRepBuilderAPI_MakeEdge(aSegment_tunc);

	TopoDS_Edge anEdge_bam = BRepBuilderAPI_MakeEdge(aSegment_bam);

	BRepBuilderAPI_MakeWire myWireTest(anEdge_base, anEdge_trunc, anEdge_up_base, anEdge_bam);

	TopoDS_Face myFaceProfile1 = BRepBuilderAPI_MakeFace(myWireTest);

	gp_Vec aPrismVec(0, 0, width);
	TopoDS_Shape myBody_base = BRepPrimAPI_MakePrism(myFaceProfile1, aPrismVec);


	//	roof

	gp_Pnt center_roof(koleso1_x + (base / 2), koleso1_y + height1, 0);

	double roof_length = length * 1 / 3;

	//	double raschet_centra = koleso_x + (base / 2);

	double up_roof_length = roof_length * 2 / 3;

	double height_roof = height - height1;


	gp_Pnt right_roof(koleso2_x + 2.5 * radius, koleso2_y + height1, 0);

	gp_Pnt left_roof(koleso2_x + 2.5 * radius - roof_length, koleso2_y + height1, 0);


	gp_Pnt left_up_roof(koleso2_x + 2.5 * radius - roof_length, koleso1_y + height1 + height_roof, 0);

	gp_Pnt right_up_roof(koleso2_x + 2.5 * radius - roof_length + up_roof_length, koleso1_y + height1 + height_roof, 0);






	Handle(Geom_TrimmedCurve) aSegment_base_roof = GC_MakeSegment(left_roof, right_roof);

	Handle(Geom_TrimmedCurve) aSegment_up_base_roof = GC_MakeSegment(left_up_roof, right_up_roof);

	Handle(Geom_TrimmedCurve) aSegment_tunc_roof = GC_MakeSegment(left_roof, left_up_roof);

	Handle(Geom_TrimmedCurve) aSegment_bam_roof = GC_MakeSegment(right_roof, right_up_roof);

	TopoDS_Edge anEdge_base_roof = BRepBuilderAPI_MakeEdge(aSegment_base_roof);

	TopoDS_Edge anEdge_up_base_roof = BRepBuilderAPI_MakeEdge(aSegment_up_base_roof);

	TopoDS_Edge anEdge_trunc_roof = BRepBuilderAPI_MakeEdge(aSegment_tunc_roof);

	TopoDS_Edge anEdge_bam_roof = BRepBuilderAPI_MakeEdge(aSegment_bam_roof);


	BRepBuilderAPI_MakeWire myWireTest2(anEdge_base_roof, anEdge_trunc_roof, anEdge_up_base_roof, anEdge_bam_roof);

	TopoDS_Face myFaceProfile2 = BRepBuilderAPI_MakeFace(myWireTest2);

	TopoDS_Shape myBody_roof = BRepPrimAPI_MakePrism(myFaceProfile2, aPrismVec);


	TopoDS_Shape superCar = BRepAlgoAPI_Fuse(myBody_base, myBody_roof);


	//trailer

	gp_Pnt left_trailer_p(koleso1_x - kef_radius * radius, koleso1_y + height1, 0);
	gp_Pnt right_trailer_p(koleso1_x - kef_radius * radius + lenght_trailer, koleso1_y + height1, 0);



	gp_Pnt left_up_trailer_p(koleso1_x - kef_radius * radius, koleso1_y + height1 + height_trailer, 0);
	gp_Pnt right_up_trailer_p(koleso1_x - kef_radius * radius + lenght_trailer, koleso1_y + height1 + height_trailer, 0);





	Handle(Geom_TrimmedCurve) aSegment_base_trailer = GC_MakeSegment(left_trailer_p, right_trailer_p);

	Handle(Geom_TrimmedCurve) aSegment_up_base_trailer = GC_MakeSegment(left_up_trailer_p, right_up_trailer_p);

	Handle(Geom_TrimmedCurve) aSegment_tunc_trailer = GC_MakeSegment(left_trailer_p, left_up_trailer_p);

	Handle(Geom_TrimmedCurve) aSegment_bam_trailer = GC_MakeSegment(right_trailer_p, right_up_trailer_p);



	TopoDS_Edge anEdge_base_trailer = BRepBuilderAPI_MakeEdge(aSegment_base_trailer);

	TopoDS_Edge anEdge_up_base_trailer = BRepBuilderAPI_MakeEdge(aSegment_up_base_trailer);

	TopoDS_Edge anEdge_trunc_trailer = BRepBuilderAPI_MakeEdge(aSegment_tunc_trailer);

	TopoDS_Edge anEdge_bam_trailer = BRepBuilderAPI_MakeEdge(aSegment_bam_trailer);



	BRepBuilderAPI_MakeWire myWireTest3(anEdge_base_trailer, anEdge_trunc_trailer, anEdge_up_base_trailer, anEdge_bam_trailer);

	TopoDS_Face myFaceProfile3 = BRepBuilderAPI_MakeFace(myWireTest3);

	TopoDS_Shape trailer = BRepPrimAPI_MakePrism(myFaceProfile3, aPrismVec);

	//car 
	TopoDS_Shape car_with_trailer = BRepAlgoAPI_Fuse(superCar, trailer);

	return car_with_trailer;

}

//airplane
TopoDS_Shape makePlain(double start_x, double start_y, double radius, double length_cylindr, double wingspan, double leng_wing, double length_tale, double height_tale) {



	const double WIDTH = 2;
	const double fit = 0.1;

	gp_Dir arow_dir;

	arow_dir = gp::DX();

	//build cylindr
	gp_Pnt cylindr_Location(start_x, start_y, 0);
	gp_Ax2 cylindr_xyz(cylindr_Location, arow_dir);
	//draw cylindr
	BRepPrimAPI_MakeCylinder MKCylinder(cylindr_xyz, radius, length_cylindr);
	TopoDS_Shape myCylindr = MKCylinder.Shape();


	gp_Pnt conus_Location;

	conus_Location.SetCoord(start_x + length_cylindr, start_y, 0);

	gp_Ax2 conus_xyz(conus_Location, arow_dir);
	//draw conus
	BRepPrimAPI_MakeCone MKCone(conus_xyz, radius, 0, length_cylindr * 1 / 5);
	TopoDS_Shape myConus = MKCone.Shape();



	//drow arow
	TopoDS_Shape myArow = BRepAlgoAPI_Fuse(myCylindr, myConus);



	double center_cyl = length_cylindr / 2;

	gp_Pnt wing_1_left(start_x + center_cyl, start_y + radius - fit, -WIDTH / 2);
	gp_Pnt wing_1_right(start_x + center_cyl + leng_wing, start_y + radius - fit, -WIDTH / 2);

	gp_Pnt wing_1_left_up(start_x + center_cyl, start_y + wingspan + radius, -WIDTH / 2);
	gp_Pnt wing_1_right_up(start_x + center_cyl + leng_wing * 2 / 3, start_y + wingspan + radius, -WIDTH / 2);

	gp_Vec aPrismVec(0, 0, WIDTH);


	Handle(Geom_TrimmedCurve) aSegment_up_wing_bottom = GC_MakeSegment(wing_1_left, wing_1_right);

	Handle(Geom_TrimmedCurve) aSegment_up_wing_up = GC_MakeSegment(wing_1_left_up, wing_1_right_up);

	Handle(Geom_TrimmedCurve) aSegment_1_left = GC_MakeSegment(wing_1_left, wing_1_left_up);

	Handle(Geom_TrimmedCurve) aSegment_1_right = GC_MakeSegment(wing_1_right, wing_1_right_up);



	TopoDS_Edge anEdge_up_wing_bottom = BRepBuilderAPI_MakeEdge(aSegment_up_wing_bottom);

	TopoDS_Edge anEdge_up_wing_up = BRepBuilderAPI_MakeEdge(aSegment_up_wing_up);

	TopoDS_Edge anEdge_1_left = BRepBuilderAPI_MakeEdge(aSegment_1_left);

	TopoDS_Edge anEdge_1_right = BRepBuilderAPI_MakeEdge(aSegment_1_right);

	BRepBuilderAPI_MakeWire myWireTest2(anEdge_up_wing_bottom, anEdge_1_left, anEdge_up_wing_up, anEdge_1_right);

	TopoDS_Face myFaceProfilewing1 = BRepBuilderAPI_MakeFace(myWireTest2);

	TopoDS_Shape myBody_wing1 = BRepPrimAPI_MakePrism(myFaceProfilewing1, aPrismVec);

	gp_Pnt mir(wing_1_left.X(), wing_1_left.Y() - radius + fit, wing_1_left.Z());

	gp_Ax1 xAxis = gp::OX();
	xAxis.SetLocation(mir);
	gp_Trsf aTrsf;

	aTrsf.SetMirror(xAxis);

	BRepBuilderAPI_Transform aBRepTrsf(myWireTest2, aTrsf);
	TopoDS_Shape aMirroredShape = aBRepTrsf.Shape();
	TopoDS_Wire aMirroredWire = TopoDS::Wire(aMirroredShape);

	TopoDS_Face myFaceProfilewing2 = BRepBuilderAPI_MakeFace(aMirroredWire);
	TopoDS_Shape myBody_wing2 = BRepPrimAPI_MakePrism(myFaceProfilewing2, aPrismVec);



	TopoDS_Shape myPlane_1 = BRepAlgoAPI_Fuse(myBody_wing1, myArow);

	TopoDS_Shape myPlane_2 = BRepAlgoAPI_Fuse(myPlane_1, myBody_wing2);



	const double chtoto = 0;

	gp_Pnt tale_left(start_x, start_y - WIDTH / 2, start_y + radius);
	gp_Pnt tale_right(start_x + length_tale, start_y - WIDTH / 2, start_y + radius);

	gp_Pnt tale_left_up(start_x, -WIDTH / 2, start_y + height_tale + radius);
	gp_Pnt tale_right_up(start_x + length_tale * 1 / 2, -WIDTH / 2, start_y + height_tale + radius);


	Handle(Geom_TrimmedCurve) aSegment_tale_bottom = GC_MakeSegment(tale_left, tale_right);

	Handle(Geom_TrimmedCurve) aSegment_up_tale_up = GC_MakeSegment(tale_left_up, tale_right_up);

	Handle(Geom_TrimmedCurve) aSegment_tale_left = GC_MakeSegment(tale_left, tale_left_up);

	Handle(Geom_TrimmedCurve) aSegment_tale_right = GC_MakeSegment(tale_right, tale_right_up);

	TopoDS_Edge anEdge_up_tale_bottom = BRepBuilderAPI_MakeEdge(aSegment_tale_bottom);

	TopoDS_Edge anEdge_up_tale_up = BRepBuilderAPI_MakeEdge(aSegment_up_tale_up);

	TopoDS_Edge anEdge_tale_left = BRepBuilderAPI_MakeEdge(aSegment_tale_left);

	TopoDS_Edge anEdge_tale_right = BRepBuilderAPI_MakeEdge(aSegment_tale_right);

	BRepBuilderAPI_MakeWire myWireTestTale(anEdge_up_tale_bottom, anEdge_tale_left, anEdge_up_tale_up, anEdge_tale_right);

	TopoDS_Face myFaceProfileTales = BRepBuilderAPI_MakeFace(myWireTestTale);

	gp_Vec aPrismVec1(0, WIDTH, 0);

	TopoDS_Shape myBody_tale = BRepPrimAPI_MakePrism(myFaceProfileTales, aPrismVec1);


	TopoDS_Shape myPlane_3 = BRepAlgoAPI_Fuse(myPlane_2, myBody_tale);

	return myPlane_3;
}

//railway carriage
TopoDS_Shape vagon(int koleso1_x, int koleso1_y, int koleso2_x, int koleso2_y, double radius, double height, double width) {

	const double kef_radius = 2.5;

	gp_Pnt koleso1(koleso1_x, koleso1_y, 0);

	gp_Pnt koleso2(koleso2_x, koleso2_y, 0);

	double base = sqrt(pow(koleso2_x - koleso1_x, 2) + pow(koleso2_y - koleso1_y, 2));

	double length = base + (kef_radius * radius) * 2;


	const double HEIGHT_V = height * 4 / 5;
	const double HEIGHT_K = height * 1 / 5;

	gp_Vec aPrismVec(length, 0, 0);

	//base
	gp_Pnt left_p(koleso2_x + kef_radius * radius, koleso1_y, 0);
	gp_Pnt right_p(koleso2_x + kef_radius * radius, koleso1_y + width, 0);




	gp_Pnt left_up_p(koleso2_x + kef_radius * radius, koleso1_y, HEIGHT_V);
	gp_Pnt right_up_p(koleso2_x + kef_radius * radius, koleso1_y + width, HEIGHT_V);


	gp_Pnt up_center(koleso2_x + kef_radius * radius, width / 2, height);

	Handle(Geom_TrimmedCurve) geometricArc_1 = GC_MakeArcOfCircle(left_up_p, up_center, right_up_p);
	TopoDS_Edge arc_edge_top = BRepBuilderAPI_MakeEdge(geometricArc_1);






	Handle(Geom_TrimmedCurve) aSegment_base = GC_MakeSegment(left_p, right_p);

	Handle(Geom_TrimmedCurve) aSegment_up_base = GC_MakeSegment(left_up_p, right_up_p);

	Handle(Geom_TrimmedCurve) aSegment_tunc = GC_MakeSegment(left_p, left_up_p);

	Handle(Geom_TrimmedCurve) aSegment_bam = GC_MakeSegment(right_p, right_up_p);

	TopoDS_Edge anEdge_base = BRepBuilderAPI_MakeEdge(aSegment_base);

	TopoDS_Edge anEdge_up_base = BRepBuilderAPI_MakeEdge(aSegment_up_base);

	TopoDS_Edge anEdge_trunc = BRepBuilderAPI_MakeEdge(aSegment_tunc);

	TopoDS_Edge anEdge_bam = BRepBuilderAPI_MakeEdge(aSegment_bam);

	BRepBuilderAPI_MakeWire myWireVagon(anEdge_base, anEdge_trunc, arc_edge_top, anEdge_bam);




	TopoDS_Face myFaceVagon = BRepBuilderAPI_MakeFace(myWireVagon);





	TopoDS_Shape myVagon = BRepPrimAPI_MakePrism(myFaceVagon, aPrismVec);


	return myVagon;
}



//set of points for gadograph
vector<gp_Pnt> points_for_gadograf() {
	vector<gp_Pnt> vec_p;


	for (int i = 0; i < 10; ++i) {
		gp_Pnt p(i, i, 0);
		vec_p.push_back(p);
	}

	for (int i = 1; i <= 10; ++i) {
		gp_Pnt p(vec_p[vec_p.size() - 1].X() - i, vec_p[vec_p.size() - 1].Y(), 0);
		vec_p.push_back(p);
	}
	for (int i = 1; i <= 5; ++i) {
		gp_Pnt p(vec_p[vec_p.size() - 1].X(), vec_p[vec_p.size() - 1].Y() + i, 0);
		vec_p.push_back(p);
	}

	for (int i = 1; i <= 5; ++i) {
		gp_Pnt p(vec_p[vec_p.size() - 1].X() - i, vec_p[vec_p.size() - 1].Y(), 0);
		vec_p.push_back(p);
	}
	for (int i = 1; i <= 10; ++i) {
		gp_Pnt p(vec_p[vec_p.size() - 1].X() + i, vec_p[vec_p.size() - 1].Y() + i, 0);
		vec_p.push_back(p);
	}
	for (int i = 1; i <= 10; ++i) {
		gp_Pnt p(vec_p[vec_p.size() - 1].X(), vec_p[vec_p.size() - 1].Y() + i, 0);
		vec_p.push_back(p);
	}

	for (int i = 1; i <= 10; ++i) {
		gp_Pnt p(vec_p[vec_p.size() - 1].X() + i, vec_p[vec_p.size() - 1].Y(), 0);
		vec_p.push_back(p);
	}
	return vec_p;
}
//gadograf 
TopoDS_Shape gadograf(vector<gp_Pnt>& pvec) {
	vector<Handle(Geom_TrimmedCurve)>aSegments;
	vector<TopoDS_Edge>anEdges;
	for (int i = 0; i < pvec.size() - 1; ++i) {


		Handle(Geom_TrimmedCurve) aSegment = GC_MakeSegment(pvec[i], pvec[i + 1]);

		aSegments.push_back(aSegment);
	}

	for (int i = 0; i < aSegments.size(); ++i) {
		TopoDS_Edge anEdge = BRepBuilderAPI_MakeEdge(aSegments[i]);
		anEdges.push_back(anEdge);
	}

	BRepBuilderAPI_MakeWire myWireTest;
	for (int i = 0; i < anEdges.size(); ++i) {
		myWireTest.Add(anEdges[i]);
	}
	gp_Vec aPrismVec(0, 0, 0.1);

	TopoDS_Shape myBody = BRepPrimAPI_MakePrism(myWireTest, aPrismVec);

	return myBody;
}
//gadograf with extinction (version 1)
void gadograf_potuh(vector<gp_Pnt>& pvec, Viewer& vout) {

	const int length = pvec.size();
	const double speed = 2;
	const int timeout = 10;
	const int time = length / speed;
	const int uchastki = time - timeout;
	const double hd = 0.1;
	const double kef = hd / uchastki;
	double utihanie = hd;
	vector<TopoDS_Shape>myGadografVec;

	int counter = 0;

	//первая тестовая линия
	for (int i = 0; i < uchastki; ++i, ++counter) {
		gp_Vec direction(pvec[i], pvec[i + 1]);
		gp_Ax2 starter(pvec[i], direction);
		double height = sqrt(pow(pvec[i + 1].X() - pvec[i].X(), 2) + pow(pvec[i + 1].Y() - pvec[i].Y(), 2));
		BRepPrimAPI_MakeCylinder myBody(starter, utihanie, height);
		utihanie -= kef;
		myGadografVec.push_back(myBody);
	}

	//вторая тестовая линия
	for (int i = 0; i < timeout - 1; ++i) {

		gp_Vec direction(pvec[counter], pvec[counter + 1]);
		gp_Ax2 starter(pvec[counter], direction);
		double height = sqrt(pow(pvec[counter + 1].X() - pvec[counter].X(), 2) + pow(pvec[counter + 1].Y() - pvec[counter].Y(), 2));

		BRepPrimAPI_MakeCylinder myBody(starter, hd, height);
		myGadografVec.push_back(myBody);
	}

	//вывод
	for (int i = 0; i < myGadografVec.size(); ++i)
		vout << myGadografVec[i];

}
//gadograf with extinction (version 2)
TopoDS_Shape gadograf_potuh_wire(vector<gp_Pnt>& pvec) {

	const int length = pvec.size();
	const double speed = 2;
	const int timeout = 10;
	const int time = length / speed;
	const int uchastki = time - timeout;
	const double hd = 5;
	const double kef = hd / uchastki;
	double utihanie = hd;
	vector<TopoDS_Shape>myGadografVec;
	BRepBuilderAPI_MakeWire myWire;
	int counter = 0;
	for (int i = 0; i < uchastki; ++i, ++counter) {
		Handle(Geom_TrimmedCurve) aSegment = GC_MakeSegment(pvec[i], pvec[i + 1]);
		TopoDS_Edge anEdge = BRepBuilderAPI_MakeEdge(aSegment);
		myWire.Add(anEdge);
	}

	for (int i = 0; i < timeout; ++i) {

		Handle(Geom_TrimmedCurve) aSegment = GC_MakeSegment(pvec[counter], pvec[counter + 1]);
		TopoDS_Edge anEdge = BRepBuilderAPI_MakeEdge(aSegment);
		myWire.Add(anEdge);
	}
	TopoDS_Shape myFinalShape = myWire.Shape();
	return myFinalShape;
}



//diametr dimension
Handle(AIS_InteractiveContext) diameterDimension(double radius, gp_Pnt pos_dimension, gp_Pnt pos_text, Viewer& vout) {
	gp_Circ gpCirc_arc_1;
	gpCirc_arc_1.SetRadius(radius);
	gpCirc_arc_1.SetLocation(pos_dimension);
	Handle(AIS_InteractiveContext) m_context = new AIS_InteractiveContext(vout.m_viewer);
	Handle(PrsDim_DiameterDimension) myDiameter = new PrsDim_DiameterDimension(gpCirc_arc_1);
	myDiameter->SetTextPosition(pos_text);
	m_context->Display(myDiameter, true);
	m_context->SetDisplayMode(myDiameter, AIS_Shaded, true);
	return m_context;

}
//angle dimension
Handle(AIS_InteractiveContext)  angleDimension( gp_Pnt dot1, gp_Pnt dot2, gp_Pnt dot3, Viewer& vout) {
	Handle(AIS_InteractiveContext) m_context = new AIS_InteractiveContext(vout.m_viewer);
	Handle(PrsDim_AngleDimension) myAngle = new PrsDim_AngleDimension(dot1, dot2, dot3);
	m_context->Display(myAngle, true);
	m_context->SetDisplayMode(myAngle, AIS_Shaded, true);
	return m_context;
}

//text(first version)
Handle(AIS_InteractiveContext) text_label(TCollection_ExtendedString text, gp_Pnt pos_text, Viewer& vout,double angle = 0) {
	Handle(AIS_TextLabel) shape_text = new AIS_TextLabel();
	Handle(AIS_InteractiveContext) m_context = new AIS_InteractiveContext(vout.m_viewer);
	shape_text->SetText(text);
	shape_text->SetAngle(angle);
	shape_text->SetPosition(pos_text);
	m_context->Display(shape_text, true);
	m_context->SetDisplayMode(shape_text, AIS_Shaded, true);
	return m_context;
}

//text (two version)
TopoDS_Shape text3dbrep(NCollection_String str_3d, double center_x, double center_y)
{


	const double aFontHeight = 20.0;
	Font_BRepFont aFont(Font_NOF_SANS_SERIF, Font_FontAspect_Bold, aFontHeight);
	Font_BRepTextBuilder aBuilder;

	gp_Pnt pepe1_1(center_x, center_y, 0);
	gp_Pnt pepe1_2(0, 20, 0);
	gp_Vec gek1(pepe1_1, pepe1_2);
	gp_Dir text_dir;
	text_dir = gp::DX();
	gp_Pnt centerP(0, 20, 0);
	gp_Ax2 gp_ax2_text(centerP, text_dir);





	TopoDS_Shape aTextShape2d = aBuilder.Perform(aFont, str_3d);

	const double anExtrusion = 5.0;
	BRepPrimAPI_MakePrism aPrismTool(aTextShape2d, gp_Vec(0, 0, 1) * anExtrusion);

	TopoDS_Shape aTextShape3d = aPrismTool.Shape();

	return aTextShape3d;
}



//scale
Handle(AIS_InteractiveContext) scale_draw (double pos_x,double pos_y,double range_min,double range_max, double size_w,double size_h,double min,double max,Viewer& vout) {
	Handle(AIS_InteractiveContext) m_context = new AIS_InteractiveContext(vout.m_viewer);
	Handle(AIS_ColorScale) scale = new AIS_ColorScale();
	scale->SetPosition(pos_x, pos_y);
	scale->SetRange(range_min, range_max);
	scale->SetSize(size_w, size_h);
	scale->SetMin(min);
	scale->SetMax(max);
	scale->SetHueRange(0, 100);
	m_context->Display(scale, true);
	m_context->SetDisplayMode(scale, AIS_Shaded, true);
	return m_context;
}


//bolt nut
TopoDS_Shape boltnut(gp_Pnt center, double radius, double length_cyl) {
	
	//nut
	TopoDS_Shape shape;
	gp_Vec aPrismVec(0, 0, 19);


	//do poligon
	gp_Pnt left_center(center.X() - radius, center.Y(), center.Z());

	gp_Pnt right_center(center.X() + radius, center.Y(), center.Z());
	
	double h = sqrt(pow(radius, 2) - pow(radius / 2, 2));

	gp_Pnt left_up(center.X() - radius/2, center.Y()+h, center.Z());

	gp_Pnt right_up(center.X() + radius / 2, center.Y() + h, center.Z());

	gp_Pnt left_down(center.X() - radius / 2, center.Y() - h, center.Z());

    gp_Pnt right_down(center.X() + radius / 2, center.Y() - h, center.Z());

	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(left_center, left_up);
	Handle(Geom_TrimmedCurve) aSegment2 = GC_MakeSegment(left_up, right_up);
	Handle(Geom_TrimmedCurve) aSegment3 = GC_MakeSegment(right_up, right_center);



	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);

	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(aSegment2);

	TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge(aSegment3);

	BRepBuilderAPI_MakeWire wirePolyTop(anEdge1, anEdge2, anEdge3);

	//symmetry
	gp_Ax1 right_xAxis = gp::OX();
	right_xAxis.SetLocation(left_center);
	gp_Trsf right_aTrsf;
	right_aTrsf.SetMirror(right_xAxis);

	BRepBuilderAPI_Transform wirePoly_transform(wirePolyTop, right_aTrsf);
	TopoDS_Shape aMirroredShape = wirePoly_transform.Shape();
	TopoDS_Wire wirePolyBottom = TopoDS::Wire(aMirroredShape);
	//do arc
	const double kef = 3;
	double radius_arc = radius / kef;

	gp_Pnt left_arc_p(center.X() - radius_arc, center.Y(), center.Z());
	gp_Pnt right_arc_p(center.X() + radius_arc, center.Y(), center.Z());
	gp_Pnt up_arc_p(center.X(), center.Y() + radius_arc, center.Z());
	gp_Pnt bottom_arc_p(center.X(), center.Y() - radius_arc, center.Z());


	gp_Circ gpCirc_arc_1;
	gpCirc_arc_1.SetRadius(radius_arc);
	gp_Pnt circle_first1(center.X(), center.Y(), 0);
	gpCirc_arc_1.SetLocation(circle_first1);
	Handle(Geom_TrimmedCurve) geometricArc_arc = GC_MakeArcOfCircle(gpCirc_arc_1, PI,- PI, true);
	TopoDS_Edge arc_edge = BRepBuilderAPI_MakeEdge(geometricArc_arc);
	BRepBuilderAPI_MakeWire wireArc(arc_edge);
	

	Handle(Geom_TrimmedCurve) geometricArc_arc_up = GC_MakeArcOfCircle(gpCirc_arc_1,0, PI, true);
	TopoDS_Edge arc_edge_up = BRepBuilderAPI_MakeEdge(geometricArc_arc_up);
	BRepBuilderAPI_MakeWire wireArc_up(arc_edge_up);

	Handle(Geom_TrimmedCurve) geometricArc_arc_bottom = GC_MakeArcOfCircle(gpCirc_arc_1, PI, PI*2, true);
	TopoDS_Edge arc_edge_bottom = BRepBuilderAPI_MakeEdge(geometricArc_arc_bottom);
	BRepBuilderAPI_MakeWire wireArc_bottom(arc_edge_bottom);
	
	


	//conection

	Handle(Geom_TrimmedCurve) connect_1= GC_MakeSegment(left_center, left_arc_p);
	TopoDS_Edge anEdge_connect_1 = BRepBuilderAPI_MakeEdge(connect_1);
	BRepBuilderAPI_MakeWire wire_connect_1(anEdge_connect_1);

	Handle(Geom_TrimmedCurve) connect_2 = GC_MakeSegment(right_arc_p,right_center);
	TopoDS_Edge anEdge_connect_2 = BRepBuilderAPI_MakeEdge(connect_2);
	BRepBuilderAPI_MakeWire wire_connect_2(anEdge_connect_2);



	//shape

	//arc_shape_top
	BRepBuilderAPI_MakeWire mkWireTop;
	mkWireTop.Add(wirePolyTop);
	mkWireTop.Add(wire_connect_1);
	mkWireTop.Add(wireArc_up);
	mkWireTop.Add(wire_connect_2);
	TopoDS_Face myFaceTop = BRepBuilderAPI_MakeFace(mkWireTop);
	TopoDS_Shape myBodyTop = BRepPrimAPI_MakePrism(myFaceTop, aPrismVec);
	//arc_shape_bottom
	BRepBuilderAPI_MakeWire mkWireBottom;
	mkWireBottom.Add(wirePolyBottom);
	mkWireBottom.Add(wire_connect_1);
	mkWireBottom.Add(wireArc_bottom);
	mkWireBottom.Add(wire_connect_2);
	
	TopoDS_Face myFaceBottom = BRepBuilderAPI_MakeFace(mkWireBottom);
	TopoDS_Shape myBodyBottom = BRepPrimAPI_MakePrism(myFaceBottom, aPrismVec);



	TopoDS_Shape nut = BRepAlgoAPI_Fuse(myBodyTop, myBodyBottom);



	
	//build cylindr
	gp_Dir arow_dir;
	arow_dir = gp::DZ();
	gp_Pnt cylindr_Location(center.X(), center.Y(), center.Z()- length_cyl / 2 + 19/2);
	gp_Ax2 cylindr_xyz(cylindr_Location, arow_dir);
	BRepPrimAPI_MakeCylinder MKCylinder(cylindr_xyz, radius_arc, length_cyl);
	TopoDS_Shape myCylindr = MKCylinder.Shape();


	
	TopoDS_Shape myTelo = BRepAlgoAPI_Fuse(myCylindr, nut);



	return myTelo;
}

//слот
TopoDS_Shape slot(gp_Pnt center,double width,double height,double length) {

	gp_Vec aPrismVec(0, 0, length);

	const double kef = 3;
	//outer frame

		//coonet outer 
	gp_Pnt left_out_connect_p(center.X() - (width) / 2, center.Y() + (height / kef) / 2 / 2, center.Z());
	gp_Pnt right_out_connect_p(center.X() + (width) / 2, center.Y() + (height / kef) / 2 / 2, center.Z());
	
	//points
	gp_Pnt left_up(center.X() - width / 2, center.Y() + height/2, center.Z());

	gp_Pnt right_up(center.X() + width / 2, center.Y() + height / 2, center.Z());

	gp_Pnt left_down(center.X() - width / 2, center.Y() - height / 2, center.Z());

	gp_Pnt right_down(center.X() + width / 2, center.Y() - height / 2, center.Z());

	Handle(Geom_TrimmedCurve) aSegmentUp = GC_MakeSegment(left_up, right_up);
	Handle(Geom_TrimmedCurve) aSegmentDown = GC_MakeSegment(left_down, right_down);


	Handle(Geom_TrimmedCurve) aSegmentLeftUp = GC_MakeSegment(left_up, left_out_connect_p);
	Handle(Geom_TrimmedCurve) aSegmentRightUp = GC_MakeSegment(right_up, right_out_connect_p);

	Handle(Geom_TrimmedCurve) aSegmentLeftBottom = GC_MakeSegment(left_out_connect_p, left_down);
	Handle(Geom_TrimmedCurve) aSegmentRighBottom = GC_MakeSegment(right_out_connect_p, right_down);


	TopoDS_Edge anEdgeUp = BRepBuilderAPI_MakeEdge(aSegmentUp);

	TopoDS_Edge anEdgeDown = BRepBuilderAPI_MakeEdge(aSegmentDown);

	TopoDS_Edge anEdgeLeftUp = BRepBuilderAPI_MakeEdge(aSegmentLeftUp);

	TopoDS_Edge anEdgeRightUp = BRepBuilderAPI_MakeEdge(aSegmentRightUp);

	TopoDS_Edge anEdgeLeftBottom = BRepBuilderAPI_MakeEdge(aSegmentLeftBottom);

	TopoDS_Edge anEdgeRightBottom = BRepBuilderAPI_MakeEdge(aSegmentRighBottom);




    //inner frame------------------------


	gp_Pnt left_in_up(center.X() - (width/ kef) / 2, center.Y() + (height/ kef) / 2, center.Z());

	gp_Pnt right_in_up(center.X() + (width / kef) / 2, center.Y() + (height / kef) / 2, center.Z());

	gp_Pnt left_in_down(center.X() - (width / kef) / 2, center.Y() - (height / kef) / 2, center.Z());

	gp_Pnt right_in_down(center.X() + (width / kef) / 2, center.Y() - (height / kef) / 2, center.Z());

	//connect in
	gp_Pnt left_in_connect_p(center.X() - (width / kef) / 2, center.Y() + (height / kef) / 2 / 2, center.Z());

	gp_Pnt right_in_connect_p(center.X() + (width / kef) / 2, center.Y() + (height / kef) / 2 / 2, center.Z());


	Handle(Geom_TrimmedCurve) aSegmentInUp = GC_MakeSegment(left_in_up, right_in_up);
	Handle(Geom_TrimmedCurve) aSegmentInDown = GC_MakeSegment(left_in_down, right_in_down);
	
	Handle(Geom_TrimmedCurve) aSegmentInUpleft = GC_MakeSegment(left_in_connect_p, left_in_up);
	Handle(Geom_TrimmedCurve) aSegmentInUpRight = GC_MakeSegment(right_in_connect_p, right_in_up);

	Handle(Geom_TrimmedCurve) aSegmentInBottomleft = GC_MakeSegment(left_in_connect_p, left_in_down);
	Handle(Geom_TrimmedCurve) aSegmentInBottomRight = GC_MakeSegment(right_in_connect_p, right_in_down);
	
	TopoDS_Edge anEdgeInUp = BRepBuilderAPI_MakeEdge(aSegmentInUp);
	TopoDS_Edge anEdgeInBottom = BRepBuilderAPI_MakeEdge(aSegmentInDown);
	
	TopoDS_Edge anEdgeInUpleft = BRepBuilderAPI_MakeEdge(aSegmentInUpleft);
	TopoDS_Edge anEdgeInUpRight = BRepBuilderAPI_MakeEdge(aSegmentInUpRight);
	
	TopoDS_Edge anEdgeInBottomleft = BRepBuilderAPI_MakeEdge(aSegmentInBottomleft);
	TopoDS_Edge anEdgeInBottomRight = BRepBuilderAPI_MakeEdge(aSegmentInBottomRight);





	//connect
	
	Handle(Geom_TrimmedCurve) aSegmentLeftConnect = GC_MakeSegment(left_out_connect_p, left_in_connect_p);
	Handle(Geom_TrimmedCurve) aSegmentRightConnect = GC_MakeSegment(right_out_connect_p, right_in_connect_p);

	TopoDS_Edge anEdgeLeftConnect = BRepBuilderAPI_MakeEdge(aSegmentLeftConnect);

	TopoDS_Edge anEdgeRightConnect = BRepBuilderAPI_MakeEdge(aSegmentRightConnect);


	//frame top
	BRepBuilderAPI_MakeWire wireFrameTop(anEdgeLeftUp, anEdgeUp, anEdgeRightUp, anEdgeRightConnect);
	wireFrameTop.Add(anEdgeInUpRight);
	wireFrameTop.Add(anEdgeInUp);
	wireFrameTop.Add(anEdgeInUpleft);
	wireFrameTop.Add(anEdgeLeftConnect);

	TopoDS_Face myFaceTop = BRepBuilderAPI_MakeFace(wireFrameTop);
	TopoDS_Shape myBodyTop = BRepPrimAPI_MakePrism(myFaceTop, aPrismVec);

	//frame bottom
	BRepBuilderAPI_MakeWire wireFrameBottom(anEdgeLeftBottom, anEdgeDown, anEdgeRightBottom, anEdgeRightConnect);
	wireFrameBottom.Add(anEdgeInBottomRight);
	wireFrameBottom.Add(anEdgeInBottom);
	wireFrameBottom.Add(anEdgeInBottomleft);
	wireFrameBottom.Add(anEdgeLeftConnect);

	TopoDS_Face myFaceBottom = BRepBuilderAPI_MakeFace(wireFrameBottom);
	TopoDS_Shape myBodyBottom = BRepPrimAPI_MakePrism(myFaceBottom, aPrismVec);


	TopoDS_Shape myTelo = BRepAlgoAPI_Fuse(myBodyTop, myBodyBottom);


	return myTelo;
}











int main(int argc, char* argv[])
{

	//screen
	Viewer vout(50, 50, 500, 500);
	Handle(AIS_InteractiveContext) m_context = new AIS_InteractiveContext(vout.m_viewer);
	

	
	//car
	//const TopoDS_Shape&shape2 = makeCar(0,0,60,0,10,40,25,40);

	//trailer
	//const TopoDS_Shape&shape2 = makeCar_with_trailer(0, 0, 100,0, 10, 35, 20, 40,80,30);

	//airplane
	//const TopoDS_Shape& shape2 = makePlain(0,0, 5,100,70,20,20,30);

	//railway carriage
	//const TopoDS_Shape& shape2 = vagon(0, 0, 60, 0, 10, 40,30);

	//spur gear
	//const TopoDS_Shape&shape2 = cylindr_broadcast(0, 0, 0, -20,5,15,1,5);

	//circular arrow
	//const TopoDS_Shape&shape2 = arc_arrow(0, 0, 10, 50, 25, 20,200);

	//arrow
    //const TopoDS_Shape&shape2 = arrow(30, 10, 5, 2, 0, 0,0);



	//hodograph
	//vector<gp_Pnt> vector_list_test = points_for_gadograf();
	//const TopoDS_Shape&shape2 = gadograf(vector_list_test);
	//const TopoDS_Shape& shape2 = gadograf_potuh_wire(vector_list_test);
    // gadograf_potuh(vector_list_test, vout);



	//polygon
	//vector<gp_Pnt> vector_list = polygon_vec_points_test();
	//const TopoDS_Shape&shape2 = polygon(vector_list, 20);


	//bevel gear
	//const TopoDS_Shape&shape2 = conus_broadcast(0, 0, 40, 30,60,15);

	//worm gear
	//const TopoDS_Shape& shape2 =  warm_broadcast(0, 0,7,3,20,20,2);

	//text 3d
	//const TopoDS_Shape&shape2 = text3dbrep("vladbaltgl@yandex.ru",0,0);

	//text 2d
	//m_context = text_label("Text", gp_Pnt(0, 0, 0), vout,30) ;
	
	//angle dimensions
	//m_context = angleDimension(gp_Pnt(20, 0, 0), gp_Pnt(20, 20, 0), gp_Pnt(0, 20, 0), vout);
	
	//diameter dimensions
	//m_context =diameterDimension(50, gp_Pnt(0, 0, 0), gp_Pnt (0, 20, 0), vout) ;
	
	//scale
	//m_context =scale_draw(0,0,0,50,300,500,0,500,vout);

	//two node bracket
	//const TopoDS_Shape&shape2 = bracket( 0,0, -100, 50,30, 10);
	
	//third node bracket
	//const TopoDS_Shape&shape2 = bracket( 0,0, 30, 30, -30,-30,11, 5,1);
		
	//four node bracket 
	//const TopoDS_Shape& shape2 = bracket(0, 0, 20, 0, 20, 20, 0, 20, 7, 3, 3, 3);
	
	



	//bolt nut
	//const TopoDS_Shape& shape2 = boltnut(gp_Pnt(0,0,0),50,100);


	//slot
	//const TopoDS_Shape& shape2 = slot(gp_Pnt(0, 0, 0), 100, 50,100);



	//вывор фигуры
	//vout << shape2;
	vout.StartMessageLoop();

	return 0;
}


