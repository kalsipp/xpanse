// #include "../engine/components/transform.hpp"

// void assert_moving_position() {
// 	assert(Vector3D() == Vector3D());
// 	assert(Vector3D(1, 2, 3) != Vector3D(0, 0, 0));
// 	Transform root;
// 	assert(root.position() == Vector3D(0, 0, 0));
// 	assert(root.absolute_position() == Vector3D(0, 0, 0));

// 	root.position() += Vector3D(1, 2, 3);
// 	assert(root.position() == Vector3D(1, 2, 3));
// 	assert(root.absolute_position() == Vector3D(1, 2, 3));

// 	root.position() -= Vector3D(3, 2, 1);
// 	assert(root.position() == Vector3D(-2, 0, 2));
// 	assert(root.absolute_position() == Vector3D(-2, 0, 2));

// 	root.position() = Vector3D(0, 0, 0);
// 	assert(root.position() == Vector3D(0, 0, 0));
// 	assert(root.absolute_position() == Vector3D(0, 0, 0));
// }

// void moving_one_level_parent() {
// 	Transform root;
// 	Transform t1;

// 	t1.set_parent(&root);
// 	assert(t1.position() == Vector3D(0, 0, 0));
// 	assert(root.position() == Vector3D(0, 0, 0));

// 	t1.position() += Vector3D(1, 2, 3);
// 	assert(t1.position() == Vector3D(1, 2, 3));
// 	assert(root.position() == Vector3D(0, 0, 0));

// 	t1.position() -= Vector3D(3, 2, 1);
// 	assert(t1.position() == Vector3D(-2, 0, 2));
// 	assert(root.position() == Vector3D(0, 0, 0));

// 	t1.position() = Vector3D(1, 2, 3);
// 	root.position() += Vector3D(1, 2, 3);
// 	assert(t1.position() == Vector3D(1, 2, 3));
// 	assert(t1.absolute_position() == Vector3D(2, 4, 6));
// 	assert(root.position() == Vector3D(1, 2, 3));

// 	root.position() -= Vector3D(3, 2, 1);
// 	assert(t1.position() == Vector3D(1, 2, 3));
// 	assert(t1.absolute_position() == Vector3D(-1, 2, 5));
// 	assert(root.position() == Vector3D(-2, 0, 2));
// }
// void moving_second_level_parent() {
// 	Transform root;
// 	Transform t1;
// 	Transform t2;
// 	t1.set_parent(&root);
// 	t2.set_parent(&t1);

// 	assert(t1.position() == Vector3D(0, 0, 0));
// 	assert(t2.position() == Vector3D(0, 0, 0));
// 	assert(root.position() == Vector3D(0, 0, 0));

// 	t2.position() += Vector3D(1, 2, 3);
// 	assert(t2.position() == Vector3D(1, 2, 3));
// 	assert(t1.position() == Vector3D(0, 0, 0));
// 	assert(root.position() == Vector3D(0, 0, 0));

// 	t2.position() -= Vector3D(3, 2, 1);
// 	assert(t2.position() == Vector3D(-2, 0, 2));
// 	assert(t1.position() == Vector3D(0, 0, 0));
// 	assert(root.position() == Vector3D(0, 0, 0));

// 	t2.position() = Vector3D(0, 0, 0);
// 	t1.position() += Vector3D(1, 2, 3);
// 	assert(t1.position() == Vector3D(1, 2, 3));
// 	assert(t1.absolute_position() == Vector3D(1, 2, 3));

// 	assert(t2.position() == Vector3D(0, 0, 0));
// 	assert(t2.absolute_position() == Vector3D(1, 2, 3));

// 	assert(root.position() == Vector3D(0, 0, 0));
// 	assert(root.absolute_position() == Vector3D(0, 0, 0));

// 	root.position() = Vector3D();
// 	t1.position() = Vector3D();
// 	t2.position() = Vector3D();
// 	root.position() += Vector3D(1, 2, 3);
// 	assert(t1.position() == Vector3D());
// 	assert(t2.position() == Vector3D());
// 	assert(t1.absolute_position() == Vector3D(1, 2, 3));
// 	assert(t2.absolute_position() == Vector3D(1, 2, 3));
// 	t1.position() += Vector3D(3, 2, 1);
// 	assert(root.position() == Vector3D(1, 2, 3));
// 	assert(root.absolute_position() == Vector3D(1, 2, 3));
// 	assert(t1.position() == Vector3D(3, 2, 1));
// 	assert(t1.absolute_position() == Vector3D(4, 4, 4));
// 	assert(t2.position() == Vector3D());
// 	assert(t2.absolute_position() == Vector3D(4, 4, 4));
// }

// void moving_root(){
// 	Transform t1;
// 	Transform t2;
// 	assert(t1.get_root_parent().position() == Vector3D());
// 	assert(t1.get_root_parent().absolute_position() == Vector3D());
// 	assert(t2.get_root_parent().position() == Vector3D());
// 	assert(t2.get_root_parent().absolute_position() == Vector3D());
	  
// 	t1.set_root_parent_position(Vector3D(1,2,3));
// 	assert(t1.position() == Vector3D());
// 	assert(t1.absolute_position() == Vector3D(1,2,3));
// 	assert(t1.get_root_parent().position() == Vector3D(1,2,3));
// 	assert(t1.get_root_parent().absolute_position() == Vector3D(1,2,3));

// 	assert(t2.position() == Vector3D());
// 	assert(t2.absolute_position() == Vector3D(1,2,3));
// 	assert(t2.get_root_parent().position() == Vector3D(1,2,3));
// 	assert(t2.get_root_parent().absolute_position() == Vector3D(1,2,3));
	
// 	t1.set_root_parent_position(Vector3D());

// 	t1.move_root_parent_position(Vector3D(1,2,3));
// 	assert(t1.position() == Vector3D());
// 	assert(t1.absolute_position() == Vector3D(1,2,3));
// 	assert(t1.get_root_parent().position() == Vector3D(1,2,3));
// 	assert(t1.get_root_parent().absolute_position() == Vector3D(1,2,3));
// 	assert(t2.position() == Vector3D());
// 	assert(t2.absolute_position() == Vector3D(1,2,3));
// 	assert(t2.get_root_parent().position() == Vector3D(1,2,3));
// 	assert(t2.get_root_parent().absolute_position() == Vector3D(1,2,3));
// }
// void constructors(){
// 	Transform t1;
// 	Transform t2 = Transform();
// 	Transform * t3 = new Transform(t2);
// 	Transform * t4 = new Transform(t3);
// 	t3->position() = Vector3D(1,2,3);
// 	assert(t4->absolute_position()==Vector3D(1,2,3));
// 	delete t3;
// 	assert(t4->absolute_position()==Vector3D(1,2,3));
// 	Transform t5(t2);
// 	t1 = t5;
// }

int main() {
// 	assert_moving_position();
// 	moving_one_level_parent();
// 	moving_second_level_parent();
// 	moving_root();
// 	constructors();
}