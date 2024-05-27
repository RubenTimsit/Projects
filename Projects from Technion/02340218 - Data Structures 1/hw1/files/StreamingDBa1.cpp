#include "StreamingDBa1.h"
#include "AVLTree.h"
using std::shared_ptr;










streaming_database::streaming_database() : groupsTree(Group::compareGroups),usersTree(User::compareUsers),
                                           moviesTree(Movie::compareMovies), comedyTree(Movie::compareGenre),dramaTree(Movie::compareGenre),
                                           actionTree(Movie::compareGenre), fantasyTree(Movie::compareGenre),
                                           allMoviesAccordingToGrade(Movie::compareGenre),
                                           comedyTreeSize(0),dramaTreeSize(0),actionTreeSize(0),fantasyTreeSize(0),highestComedyID(0),
                                           highestDramaID(0),highestActionID(0),highestFantasyID(0)
{

}

streaming_database::~streaming_database()
{
    shared_ptr<User> temp[usersTree.getTreeSize()];
    usersTree.toArray(temp);
    for(int i = 0;i<usersTree.getTreeSize();i++) {
        temp[i]->setGroupPTR(nullptr);
        temp[i]->setGroupID(0);
    }
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if(movieId <=0 || genre == Genre::NONE || views < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Movie> tempMovie(new Movie(movieId,genre,views,vipOnly));
    if(tempMovie == nullptr)
        return StatusType::ALLOCATION_ERROR;
    auto *movieNode = moviesTree.find(tempMovie);
    if(movieNode != nullptr)
    {
        return StatusType::FAILURE;
    }
    try {
        moviesTree.insertNode(tempMovie);
        allMoviesAccordingToGrade.insertNode(tempMovie);
    }
    catch (const std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }

    switch(genre)
    {

        case Genre::COMEDY: {
            comedyTree.insertNode(tempMovie);
            comedyTreeSize++;
            highestComedyID = comedyTree.findMaxNode(comedyTree.getRoot())->getValue()->getId();
            break;
        }

        case Genre::DRAMA: {
            dramaTree.insertNode(tempMovie);
            dramaTreeSize++;
            highestDramaID = dramaTree.findMaxNode(dramaTree.getRoot())->getValue()->getId();
            break;
        }

        case Genre::ACTION: {
            actionTree.insertNode(tempMovie);
            actionTreeSize++;
            highestActionID = actionTree.findMaxNode(actionTree.getRoot())->getValue()->getId();
            break;
        }

        case Genre::FANTASY: {
            fantasyTree.insertNode(tempMovie);
            fantasyTreeSize++;
            highestFantasyID = fantasyTree.findMaxNode(fantasyTree.getRoot())->getValue()->getId();
            break;
        }

        default:
            break;
    }
	return StatusType::SUCCESS;
}


StatusType streaming_database::remove_movie(int movieId)
{
    if(movieId <= 0) {
        return StatusType::INVALID_INPUT;
    }
	shared_ptr<Movie> tempMovie( new Movie(movieId,Genre::NONE,0,false));
    if(tempMovie == nullptr)
        return StatusType::ALLOCATION_ERROR;
    auto *movieNode = this->moviesTree.find(tempMovie);
    if(movieNode == nullptr)
    {
        return StatusType::FAILURE;
    }
    tempMovie = movieNode->getValue();

    switch(tempMovie->getGenre())
    {

        case Genre::COMEDY:
            comedyTree.removeNode(tempMovie);
            comedyTreeSize--;
            if(comedyTreeSize > 0)
                highestComedyID = comedyTree.findMaxNode(comedyTree.getRoot())->getValue()->getId();
            else highestComedyID = 0;
            break;

        case Genre::DRAMA:
            dramaTree.removeNode(tempMovie);
            dramaTreeSize--;
            if(dramaTreeSize > 0)
                highestDramaID = dramaTree.findMaxNode(dramaTree.getRoot())->getValue()->getId();
            else highestDramaID = 0;
            break;

        case Genre::ACTION:
            actionTree.removeNode(tempMovie);
            actionTreeSize--;
            if(actionTreeSize > 0)
                highestActionID = actionTree.findMaxNode(actionTree.getRoot())->getValue()->getId();
            else highestActionID = 0;
            break;

        case Genre::FANTASY:
            fantasyTree.removeNode(tempMovie);
            fantasyTreeSize--;
            if(fantasyTreeSize > 0)
                highestFantasyID = fantasyTree.findMaxNode(fantasyTree.getRoot())->getValue()->getId();
            else highestFantasyID = 0;
            break;

        case Genre::NONE:
            break;
    }
    try {
        allMoviesAccordingToGrade.removeNode(tempMovie);
        moviesTree.removeNode(tempMovie);
    }
    catch (const std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
    if(userId <= 0)
        return StatusType::INVALID_INPUT;
    shared_ptr<User> tempUser(new User(userId, isVip));
    if(tempUser == nullptr)
        return StatusType::ALLOCATION_ERROR;
    auto *userNode = usersTree.find(tempUser);
    if(userNode != nullptr ){ // no need to delete, smart ptr
        return StatusType::FAILURE;
    }
    try {
        usersTree.insertNode(tempUser);
    }
    catch (const std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}


StatusType streaming_database::remove_user(int userId)
{
    if(userId <= 0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<User> tempUser(new User(userId, false));
    if(tempUser == nullptr)
        return StatusType::ALLOCATION_ERROR;
    auto *userNode = this->usersTree.find(tempUser);
    if(userNode == nullptr)
        return StatusType::FAILURE;
    tempUser = userNode->getValue();
    if(tempUser->getGroupID() != 0)
        tempUser->getGroupPTR()->removeUser(tempUser);
    try {
        usersTree.removeNode(tempUser);
    }
    catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
    if(groupId <= 0)
        return StatusType::INVALID_INPUT;
    shared_ptr<Group> tempGroup(new Group(groupId));
    if(tempGroup == nullptr)
        return StatusType::ALLOCATION_ERROR;
    auto *groupNode = groupsTree.find(tempGroup);
    if(groupNode != nullptr ){ // no need to delete, smart ptr
        return StatusType::FAILURE;
    }
    try {
        groupsTree.insertNode(tempGroup);
    }
    catch (const std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}


StatusType streaming_database::remove_group(int groupId)
{
    if(groupId <= 0)
        return StatusType::INVALID_INPUT;
    shared_ptr<Group> tempGroup(new Group(groupId));
    if(tempGroup == nullptr)
        return StatusType::ALLOCATION_ERROR;
    auto *groupNode = this->groupsTree.find(tempGroup);
    if(groupNode == nullptr)
        return StatusType::FAILURE;
    tempGroup = groupNode->getValue();
    try {
        tempGroup->removeMe();
        groupsTree.removeNode(tempGroup);
    }
    catch (const std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    if(userId <= 0 || groupId <= 0)
        return StatusType::INVALID_INPUT;

    shared_ptr<User> user(new User(userId, false));
    if(user == nullptr)
        return StatusType::ALLOCATION_ERROR;
    auto *userNode = usersTree.find(user);

    shared_ptr<Group> group(new Group(groupId));
    if(group == nullptr)
        return StatusType::ALLOCATION_ERROR;
    auto *groupNode = groupsTree.find(group);

    if(userNode == nullptr || groupNode == nullptr || userNode->getValue()->getGroupID() != 0)
        return StatusType::FAILURE;

    user = userNode->getValue();
    try {
        groupNode->getValue()->addUser(user);
    }
    catch (const std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    if(userId <= 0 || movieId <= 0)
        return StatusType::INVALID_INPUT;

    //////////Get User//////////
    shared_ptr<User> user(new User(userId, false));
    if(user == nullptr)
        return StatusType::ALLOCATION_ERROR;
    auto *userNode = usersTree.find(user);
    if(userNode == nullptr)
        return StatusType::FAILURE;
    user = userNode->getValue();

    //////////Get Movie//////////
    shared_ptr<Movie> tempMovie( new Movie(movieId,Genre::NONE,0,false));
    if(tempMovie == nullptr)
        return StatusType::ALLOCATION_ERROR;
    auto *movieNode = this->moviesTree.find(tempMovie);
    if(movieNode == nullptr)
        return StatusType::FAILURE;
    tempMovie = movieNode->getValue();


    if(tempMovie->getIsVIP() && !user->getVIP())
        return StatusType::FAILURE;


    user->setGenre(int(tempMovie->getGenre()));

    switch (int(tempMovie->getGenre())) {
        case 0: {//COMEDY
            updateTrees(comedyTree, tempMovie, 1, 0, MovieAction::VIEWS);
            highestComedyID = comedyTree.findMaxNode(comedyTree.getRoot())->getValue()->getId();
            break;
        }
        case 1: {//DRAMA
            updateTrees(dramaTree, tempMovie, 1, 0, MovieAction::VIEWS);
            highestDramaID = dramaTree.findMaxNode(dramaTree.getRoot())->getValue()->getId();
            break;
        }
        case 2: {//ACTION
            updateTrees(actionTree, tempMovie, 1, 0, MovieAction::VIEWS);
            highestActionID = actionTree.findMaxNode(actionTree.getRoot())->getValue()->getId();
            break;
        }
        case 3: {//FANTASY
            updateTrees(fantasyTree, tempMovie, 1, 0, MovieAction::VIEWS);
            highestFantasyID = fantasyTree.findMaxNode(fantasyTree.getRoot())->getValue()->getId();
            break;
        }
        default: ;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    if(groupId <= 0 || movieId <= 0)
        return StatusType::INVALID_INPUT;

    //////////Get Group//////////
    shared_ptr<Group> group(new Group(groupId));
    if(group == nullptr)
        return StatusType::ALLOCATION_ERROR;
    auto *groupNode = groupsTree.find(group);
    if(groupNode == nullptr)
        return StatusType::FAILURE;
    group = groupNode->getValue();

    //////////Get Movie//////////
    shared_ptr<Movie> tempMovie( new Movie(movieId,Genre::NONE,0,false));
    if(tempMovie == nullptr)
        return StatusType::ALLOCATION_ERROR;
    auto *movieNode = this->moviesTree.find(tempMovie);
    if(movieNode == nullptr)
        return StatusType::FAILURE;
    tempMovie = movieNode->getValue();

    if((!group->getVIP() && tempMovie->getIsVIP()) || group->getSize() <= 0)
        return StatusType::FAILURE;
    group->setGenreCombined(int(tempMovie->getGenre()),1);
    group->setGenreGroup(int(tempMovie->getGenre()));

    switch (int(tempMovie->getGenre())) {
        case 0: {//COMEDY
            updateTrees(comedyTree, tempMovie, group->getSize(), 0, MovieAction::VIEWS);
            highestComedyID = comedyTree.findMaxNode(comedyTree.getRoot())->getValue()->getId();
            break;
        }
        case 1: {//DRAMA
            updateTrees(dramaTree, tempMovie, group->getSize(), 0, MovieAction::VIEWS);
            highestDramaID = dramaTree.findMaxNode(dramaTree.getRoot())->getValue()->getId();
            break;
        }
        case 2: {//ACTION
            updateTrees(actionTree, tempMovie, group->getSize(), 0, MovieAction::VIEWS);
            highestActionID = actionTree.findMaxNode(actionTree.getRoot())->getValue()->getId();
            break;
        }
        case 3: {//FANTASY
            updateTrees(fantasyTree, tempMovie, group->getSize(), 0, MovieAction::VIEWS);
            highestFantasyID = fantasyTree.findMaxNode(fantasyTree.getRoot())->getValue()->getId();
            break;
        }
        default: ;
    }

    return StatusType::SUCCESS;
}


output_t<int> streaming_database::get_all_movies_count(Genre genre) const
{
    switch(genre)
    {

        case Genre::COMEDY: {
            return comedyTreeSize;
        }

        case Genre::DRAMA: {
            return dramaTreeSize;
        }

        case Genre::ACTION: {
            return actionTreeSize;
        }

        case Genre::FANTASY: {
            return fantasyTreeSize;
        }

        case Genre::NONE:
            int size = comedyTreeSize+actionTreeSize+dramaTreeSize+fantasyTreeSize;
            return size;
    }
    return StatusType::SUCCESS;

}


StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    if(output == nullptr)
    {
        return StatusType::INVALID_INPUT;
    }
    switch (genre) {

        case Genre::COMEDY: {
            if (comedyTree.isEmpty()) {
                return StatusType::FAILURE;
            }
            shared_ptr<Movie> temp[comedyTreeSize];
            comedyTree.toArray(temp);
            for (int i = 0; i < comedyTreeSize; i++) {
                output[i] = temp[comedyTreeSize - i - 1]->getId();
            }
            return StatusType::SUCCESS;
        }
        case Genre::DRAMA: {
            if (dramaTree.isEmpty()) {
                return StatusType::FAILURE;
            }
            shared_ptr<Movie> temp[dramaTreeSize];
            dramaTree.toArray(temp);
            for (int i = 0; i < dramaTreeSize; i++) {
                output[i] = temp[dramaTreeSize - i - 1]->getId();
            }
            return StatusType::SUCCESS;
        }

        case Genre::ACTION: {
            if (actionTree.isEmpty()) {
                return StatusType::FAILURE;
            }
            shared_ptr<Movie> temp[actionTreeSize];
            actionTree.toArray(temp);
            for (int i = 0; i < actionTreeSize; i++) {
                output[i] = temp[actionTreeSize - i - 1]->getId();
            }
            return StatusType::SUCCESS;
        }
        case Genre::FANTASY: {
            if (fantasyTree.isEmpty()) {
                return StatusType::FAILURE;
            }
            shared_ptr<Movie> temp[fantasyTreeSize];
            fantasyTree.toArray(temp);
            for (int i = 0; i < fantasyTreeSize; i++) {
                output[i] = temp[fantasyTreeSize - i - 1]->getId();
            }
            return StatusType::SUCCESS;
        }
        case Genre::NONE: {
            int size = fantasyTreeSize + actionTreeSize + comedyTreeSize + dramaTreeSize;

            if (allMoviesAccordingToGrade.isEmpty()) {
                return StatusType::FAILURE;
            }
            shared_ptr<Movie> temp[size];
            allMoviesAccordingToGrade.toArray(temp);
            for (int i = 0; i < size; i++) {
                output[i] = temp[size - i - 1]->getId();
            }
            return StatusType::SUCCESS;
        }
    }

    return StatusType::FAILURE;
}


output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{


    int view_num = 0;
    if(userId<=0)
        return StatusType::INVALID_INPUT;
    shared_ptr<User> user(new User(userId, false));
    if(user == nullptr)
        return StatusType::ALLOCATION_ERROR;
    auto *userNode = usersTree.find(user);
    if(userNode == nullptr)
        return StatusType::FAILURE;
    user = userNode->getValue();

    if(genre == Genre::NONE){
        for(int i = 0; i<5;i++)
            view_num += user->getCurrGenre(i);
        return view_num;
    }
    view_num = user->getCurrGenre(int(genre));
    return view_num;

}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    if(movieId <=0 || userId <=0 || rating < 0 || rating > 100)
    {
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<User> tempUser(new User(userId, false));
    if(tempUser == nullptr)
        return StatusType::ALLOCATION_ERROR;
    auto *userNode = this->usersTree.find(tempUser);
    if(userNode == nullptr)
        return StatusType::FAILURE;
    tempUser = userNode->getValue();

    shared_ptr<Movie> tempMovie( new Movie(movieId,Genre::NONE,0,false));
    auto *movieNode = this->moviesTree.find(tempMovie);
    if(movieNode == nullptr)
        return StatusType::FAILURE;
    tempMovie = movieNode->getValue();

    if(tempMovie->getIsVIP())
    {
        if(!tempUser->getVIP())
        {
            return StatusType::FAILURE;
        }
    }

    switch (int(tempMovie->getGenre())) {
        case 0: {//COMEDY
            updateTrees(comedyTree, tempMovie, 0, rating, MovieAction::RATING);
            highestComedyID = comedyTree.findMaxNode(comedyTree.getRoot())->getValue()->getId();
            break;
        }
        case 1: {//DRAMA
            updateTrees(dramaTree, tempMovie, 0, rating, MovieAction::RATING);
            highestDramaID = dramaTree.findMaxNode(dramaTree.getRoot())->getValue()->getId();
            break;
        }
        case 2: {//ACTION
            updateTrees(actionTree, tempMovie, 0, rating, MovieAction::RATING);
            highestActionID = actionTree.findMaxNode(actionTree.getRoot())->getValue()->getId();
            break;
        }
        case 3: {//FANTASY
            updateTrees(fantasyTree, tempMovie, 0, rating, MovieAction::RATING);
            highestFantasyID = fantasyTree.findMaxNode(fantasyTree.getRoot())->getValue()->getId();
            break;
        }
        default: ;
    }


    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
    if(groupId <= 0)
        return StatusType::INVALID_INPUT;
    shared_ptr<Group> group(new Group(groupId));
    if(group == nullptr)
        return StatusType::ALLOCATION_ERROR;
    auto *groupNode = groupsTree.find(group);
    if(groupNode == nullptr)
        return StatusType::FAILURE;
    group = groupNode->getValue();
    int genre = group->getFavoriteGenre();

    if(group->getSize() == 0)
        return StatusType::FAILURE;

    switch (genre)  {
        case 0: {//COMEDY
            return (highestComedyID == 0) ? output_t<int>(StatusType::FAILURE) : highestComedyID;
        }

        case 1: {//DRAMA
            return (highestDramaID == 0) ? output_t<int>(StatusType::FAILURE) : highestDramaID;
        }
        case 2: {//ACTION
            return (highestActionID == 0) ? output_t<int>(StatusType::FAILURE) : highestActionID;
        }
        case 3: {//FANTASY
            return (highestFantasyID == 0) ? output_t<int>(StatusType::FAILURE) : highestFantasyID;
        }
        default: {
            return (highestComedyID == 0) ? output_t<int>(StatusType::FAILURE) : highestComedyID;
//
        }
    }

}


void streaming_database::updateTrees(AVLTree<shared_ptr<Movie>> &movieTree, shared_ptr<Movie> &movie, int viewsToAdd, int ratingToAdd, MovieAction action)
{


    movieTree.removeNode(movie);
    allMoviesAccordingToGrade.removeNode(movie);
    if(action == MovieAction::VIEWS)
        movie->setViews(viewsToAdd);
    else if (action == MovieAction::RATING)
        movie->setRatingSUM(ratingToAdd);
    movieTree.insertNode(movie);
    allMoviesAccordingToGrade.insertNode(movie);
}



