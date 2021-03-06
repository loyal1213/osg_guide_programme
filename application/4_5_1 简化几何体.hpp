#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/StateSetManipulator>

#include <osgUtil/Optimizer>
#include <osgUtil/Simplifier>


void TestSimplifier(){

	// 创建 viewer 对象， 场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	// 切换网格模式，方便比较模型
	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// 设置样本比率， 样本比率越大， 简化越少
	// 样本比率越小， 简化越多
	float sampleRatio = 0.3f;
	// 设置点的最大误差
	float maxError = 4.0f;

	// 创建简化对象
	osgUtil::Simplifier simplifier(sampleRatio,maxError);

	// 读取牛的模型
	osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile("cow.osg");

	// 深拷贝牛的模型到 node2 节点
	osg::ref_ptr<osg::Node> node2 = (osg::Node*)(node1->clone(osg::CopyOp::DEEP_COPY_ALL));

	// 创建一个位置变换节点
	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
	// 设置位置
	pat->setPosition(osg::Vec3(10.0f,10.0f,0.0f));
	// 添加子节点
	pat->addChild(node2);
	// 简化处理
	pat->accept(simplifier);

	root->addChild(node1);
	root->addChild(pat);

	// 优化场景
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());

	viewer->realize();
	viewer->run();

}