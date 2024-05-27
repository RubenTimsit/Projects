//
// Created by Ruben on 03/05/2023.
//

#include "Movie.h"


Movie::Movie(int movieID, Genre genre, int views, bool isVIP): movieID(movieID),genre(genre), views(views),isVIP(isVIP),
ratingSUM(0),numberOfElector(0)
             {
             };

int Movie::getId() const
{
    return movieID;
}

int Movie::getViews() const
{
    return views;
}

void Movie::setViews(int viewsToAdd)
{
    views += viewsToAdd;
}

bool Movie::getIsVIP() const
{
    return isVIP;
}

Genre Movie::getGenre() const
{
    return genre;
}

int Movie::getRatingSUM() const
{
    return ratingSUM;
}

void Movie::setRatingSUM(int rateToAdd)
{
    ratingSUM += rateToAdd;
    setNumberOfElector(1);
}

int Movie::getNumberOfElector() const
{
    return numberOfElector;
}

void Movie::setNumberOfElector(int electorToAdd)
{
    numberOfElector+= electorToAdd;
}

double Movie::getAverageRating() const
{
    if(numberOfElector <= 0)
        return 0;
    double average = double(ratingSUM) / numberOfElector;
    return average;

}

int Movie::compareMovies(const shared_ptr<Movie> &a, const shared_ptr<Movie> &b) {
    int a_id = a->getId();
    int b_id = b->getId();
    if (a_id > b_id)
        return 1;
    else if (a_id == b_id)
        return 0;
    else
        return -1;
}

int Movie::compareGenre(const shared_ptr<Movie> &a, const shared_ptr<Movie> &b) {
    double a_rate = a->getAverageRating();
    double b_rate = b->getAverageRating();
    if (a_rate > b_rate)
    {
        return 1;
    }
    else if(a_rate == b_rate)
    {
        if(a->getViews() > b->getViews())
        {
            return 1;
        }
        else if(a->getViews() < b->getViews())
        {
            return -1;
        }
        else
        {
            if(a->getId() < b->getId())
            {
                return 1;
            }
            else if(a->getId() > b->getId())
            {
                return -1;
            }
            return 0;
        }
    }
    else
    {
        return -1;
    }


}
