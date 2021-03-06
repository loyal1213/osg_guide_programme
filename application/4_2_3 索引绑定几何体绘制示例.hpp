#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>
/* 绘制并渲染几何体的主要步骤
(1)  创建各种向量数据  顶点、纹理坐标、颜色、法线
(2)  示例化一个几何体对象(osg::Geometry), 设置 顶点坐标数组、纹理坐标数组、颜色数组、 法线数组、 绑定方式、 数据解析
(3)  加入叶节点绘制并渲染
*/
// 创建一个四边形节点
osg::ref_ptr<osg::Node> CreateQuad2(){

	// 创建一个叶子节点对象
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	// 创建一个几何体对象
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

	// 创建顶点数组，注意顶点的添加顺序是逆时针的
	osg::ref_ptr<osg::Vec3Array> vertex = new osg::Vec3Array();

	vertex->push_back(osg::Vec3(0.0f,  0.0f, 0.0f));
	vertex->push_back(osg::Vec3(1.0f,  0.0f, 0.0f));
	vertex->push_back(osg::Vec3(1.0f,  0.0f, 1.0f));
	vertex->push_back(osg::Vec3(0.0f,  0.0f, 1.0f));
	vertex->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

	// 设置顶点数据
	geometry->setVertexArray(vertex.get());


	// 创建四边形顶点索引数组，指定绘图基元为四边形， 注意添加顺序
	osg::ref_ptr<osg::DrawElementsUInt> quad = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS,0);
	// 添加数据
	quad->push_back(0);
	quad->push_back(1);
	quad->push_back(2);
	quad->push_back(3);
	
	// 添加到几何体
	geometry->addPrimitiveSet(quad);

	// 创建三角形顶点索引数组，指定绘制图基元为三角形，注意添加顺序
	osg::ref_ptr<osg::DrawElementsUInt> triangle = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES,0);
	// 添加数据
	triangle->push_back(4);
	triangle->push_back(0);
	triangle->push_back(3);

	// 添加到几何体
	geometry->addPrimitiveSet(triangle);


	// 创建纹理坐标
	osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();
	// 添加数据
	vt->push_back(osg::Vec2(0.0f,0.0f));
	vt->push_back(osg::Vec2(1.0f,0.0f));
	vt->push_back(osg::Vec2(1.0f,1.0f));
	vt->push_back(osg::Vec2(0.0f,1.0f));


	// 设置纹理坐标
	geometry->setTexCoordArray(0,vt.get());

	// 创建颜色数组
	osg::ref_ptr<osg::Vec4Array> v4_color = new osg::Vec4Array();
	v4_color->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	v4_color->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	v4_color->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	v4_color->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));

	// 创建颜色索引数组
	osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType,4,4>* colorIndex = new osg::TemplateIndexArray<unsigned int,osg::Array::UIntArrayType,4,4>();
	// 添加数据，注意添加顺序与顶点顺序 一 一 对应
	colorIndex->push_back(0);
	colorIndex->push_back(1);
	colorIndex->push_back(2);
	colorIndex->push_back(3);
	colorIndex->push_back(2);

	/*osg::Vec3Array* vecarray = new osg::Vec3Array;     //顶点坐标数组
	osg::UByteArray* vecindex = new osg::UByteArray;   //顶点索引数组
	osg::Vec4Array* colarray = new osg::Vec4Array;     //颜色RGB值数组
	osg::UByteArray* colindex = new osg::UByteArray;   //颜色索引数组
	osg::Vec3Array* norarray = new osg::Vec3Array;     //法线坐标数组
	osg::UByteArray* norindex = new osg::UByteArray;   //法线索引数组*/

	// 设置颜色数组
	geometry->setColorArray(v4_color);
	// 设置颜色的绑定方式为单个顶点
	geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	// 设置颜色索引数组
	// geometry->setColorIndices(colorIndex);


	// 创建法线数组
	osg::ref_ptr<osg::Vec3Array> normal = new osg::Vec3Array();
	// 添加法线
	normal->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

	// 设置法线数组
	geometry->setNormalArray(normal.get());
	geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

	// 添加图元，绘制图元为四边形
	// geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));

	// 添加到叶子节点
	geode->addChild(geometry);

	return geode;
}


void TestQuad2(){
	// 创建 viewer 对象， 场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	root->addChild(CreateQuad2());

	// 优化场景
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());

	viewer->realize();
	viewer->run();
}

