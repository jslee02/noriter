#include <dart5/dart>

using namespace dart;

void introduce(World* _world)
{
  std::cout << "Hello, my name is [" << _world->getName() << "]!" << std::endl
            << "I have [" << _world->getSkeletonCount() << "] skeletons. "
            << "Please meet my skeletons." << std::endl;

  for (int i = 0; i < _world->getSkeletonCount(); ++i)
  {
//    _world->getSkeleton()
  }
}

int main()
{
  World* world = new World("Fantastic World");

  // Skeletons
  Skeleton* skel1 = world->createSkeleton("Connor");
  Skeleton* skel2 = world->createSkeleton("Angie");

  BodyNode* body11 = skel1->createBodyNode("Link1");
  BodyNode* body12 = skel1->createBodyNode("Link2");
  BodyNode* body21 = skel2->createBodyNode("Link1");
  BodyNode* body22 = skel2->createBodyNode("Link2");

  introduce(world);

  delete world;
}
