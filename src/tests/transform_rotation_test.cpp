// #include "../engine/components/transform.hpp"

// void assert_rotating_rotation() {
// 	assert(Vector3D() == Vector3D());
// 	assert(Vector3D(1, 2, 3) != Vector3D(0, 0, 0));
// 	Transform root;
// 	assert(root.rotation() == Vector3D(0, 0, 0));
// 	assert(root.absolute_rotation() == Vector3D(0, 0, 0));

// 	root.rotation() += Vector3D(1, 2, 3);
// 	assert(root.rotation() == Vector3D(1, 2, 3));
// 	assert(root.absolute_rotation() == Vector3D(1, 2, 3));

// 	root.rotation() -= Vector3D(3, 2, 1);
// 	assert(root.rotation() == Vector3D(-2, 0, 2));
// 	assert(root.absolute_rotation() == Vector3D(-2, 0, 2));

// 	root.rotation() = Vector3D(0, 0, 0);
// 	assert(root.rotation() == Vector3D(0, 0, 0));
// 	assert(root.absolute_rotation() == Vector3D(0, 0, 0));
// }

// void rotating_one_level_parent() {
// 	Transform root;
// 	Transform t1;

// 	t1.set_parent(&root);
// 	assert(t1.rotation() == Vector3D(0, 0, 0));
// 	assert(root.rotation() == Vector3D(0, 0, 0));

// 	t1.rotation() += Vector3D(1, 2, 3);
// 	assert(t1.rotation() == Vector3D(1, 2, 3));
// 	assert(root.rotation() == Vector3D(0, 0, 0));

// 	t1.rotation() -= Vector3D(3, 2, 1);
// 	assert(t1.rotation() == Vector3D(-2, 0, 2));
// 	assert(root.rotation() == Vector3D(0, 0, 0));

// 	t1.rotation() = Vector3D(1, 2, 3);
// 	root.rotation() += Vector3D(1, 2, 3);
// 	assert(t1.rotation() == Vector3D(1, 2, 3));
// 	assert(t1.absolute_rotation() == Vector3D(2, 4, 6));
// 	assert(root.rotation() == Vector3D(1, 2, 3));

// 	root.rotation() -= Vector3D(3, 2, 1);
// 	assert(t1.rotation() == Vector3D(1, 2, 3));
// 	assert(t1.absolute_rotation() == Vector3D(-1, 2, 5));
// 	assert(root.rotation() == Vector3D(-2, 0, 2));
// }
// void rotating_second_level_parent() {
// 	Transform root;
// 	Transform t1;
// 	Transform t2;
// 	t1.set_parent(&root);
// 	t2.set_parent(&t1);

// 	assert(t1.rotation() == Vector3D(0, 0, 0));
// 	assert(t2.rotation() == Vector3D(0, 0, 0));
// 	assert(root.rotation() == Vector3D(0, 0, 0));

// 	t2.rotation() += Vector3D(1, 2, 3);
// 	assert(t2.rotation() == Vector3D(1, 2, 3));
// 	assert(t1.rotation() == Vector3D(0, 0, 0));
// 	assert(root.rotation() == Vector3D(0, 0, 0));

// 	t2.rotation() -= Vector3D(3, 2, 1);
// 	assert(t2.rotation() == Vector3D(-2, 0, 2));
// 	assert(t1.rotation() == Vector3D(0, 0, 0));
// 	assert(root.rotation() == Vector3D(0, 0, 0));

// 	t2.rotation() = Vector3D(0, 0, 0);
// 	t1.rotation() += Vector3D(1, 2, 3);
// 	assert(t1.rotation() == Vector3D(1, 2, 3));
// 	assert(t1.absolute_rotation() == Vector3D(1, 2, 3));

// 	assert(t2.rotation() == Vector3D(0, 0, 0));
// 	assert(t2.absolute_rotation() == Vector3D(1, 2, 3));

// 	assert(root.rotation() == Vector3D(0, 0, 0));
// 	assert(root.absolute_rotation() == Vector3D(0, 0, 0));

// 	root.rotation() = Vector3D();
// 	t1.rotation() = Vector3D();
// 	t2.rotation() = Vector3D();
// 	root.rotation() += Vector3D(1, 2, 3);
// 	assert(t1.rotation() == Vector3D());
// 	assert(t2.rotation() == Vector3D());
// 	assert(t1.absolute_rotation() == Vector3D(1, 2, 3));
// 	assert(t2.absolute_rotation() == Vector3D(1, 2, 3));
// 	t1.rotation() += Vector3D(3, 2, 1);
// 	assert(root.rotation() == Vector3D(1, 2, 3));
// 	assert(root.absolute_rotation() == Vector3D(1, 2, 3));
// 	assert(t1.rotation() == Vector3D(3, 2, 1));
// 	assert(t1.absolute_rotation() == Vector3D(4, 4, 4));
// 	assert(t2.rotation() == Vector3D());
// 	assert(t2.absolute_rotation() == Vector3D(4, 4, 4));
// }

// void rotating_root(){
// 	Transform t1;
// 	Transform t2;
// 	assert(t1.get_root_parent().rotation() == Vector3D());
// 	assert(t1.get_root_parent().absolute_rotation() == Vector3D());
// 	assert(t2.get_root_parent().rotation() == Vector3D());
// 	assert(t2.get_root_parent().absolute_rotation() == Vector3D());
	  
// 	t1.set_root_parent_rotation(Vector3D(1,2,3));
// 	assert(t1.rotation() == Vector3D());
// 	assert(t1.absolute_rotation() == Vector3D(1,2,3));
// 	assert(t1.get_root_parent().rotation() == Vector3D(1,2,3));
// 	assert(t1.get_root_parent().absolute_rotation() == Vector3D(1,2,3));

// 	assert(t2.rotation() == Vector3D());
// 	assert(t2.absolute_rotation() == Vector3D(1,2,3));
// 	assert(t2.get_root_parent().rotation() == Vector3D(1,2,3));
// 	assert(t2.get_root_parent().absolute_rotation() == Vector3D(1,2,3));
	
// 	t1.set_root_parent_rotation(Vector3D());

// 	t1.rotate_root_parent(Vector3D(1,2,3));
// 	assert(t1.rotation() == Vector3D());
// 	assert(t1.absolute_rotation() == Vector3D(1,2,3));
// 	assert(t1.get_root_parent().rotation() == Vector3D(1,2,3));
// 	assert(t1.get_root_parent().absolute_rotation() == Vector3D(1,2,3));
// 	assert(t2.rotation() == Vector3D());
// 	assert(t2.absolute_rotation() == Vector3D(1,2,3));
// 	assert(t2.get_root_parent().rotation() == Vector3D(1,2,3));
// 	assert(t2.get_root_parent().absolute_rotation() == Vector3D(1,2,3));
// }

// void constructors(){
// 	Transform t1;
// 	Transform t2 = Transform();
// 	Transform * t3 = new Transform(t2);
// 	Transform * t4 = new Transform(t3);
// 	t3->rotation() = Vector3D(1,2,3);
// 	assert(t4->absolute_rotation()==Vector3D(1,2,3));
// 	delete t3;
// 	assert(t4->absolute_rotation()==Vector3D(1,2,3));
// 	Transform t5(t2);
// 	t1 = t5;
// }

int main() {
// 	assert_moving_position();
// 	moving_one_level_parent();
// 	moving_second_level_parent();
// 	moving_root();
// 	assert_rotating_rotation();
// 	rotating_one_level_parent();
// 	rotating_second_level_parent();
// 	rotating_root();
// 	constructors();
}