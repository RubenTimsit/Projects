//
// Created by Ruben on 03/05/2023.
//

#include <memory>
#include "wet1util.h"
#ifndef STREAMINGDBA1_H_MOVIES_H
#define STREAMINGDBA1_H_MOVIES_H


using std::shared_ptr;

enum struct MovieAction {
    VIEWS          = 0,
    RATING = 1,
};

class Movie{
private:
    int movieID;
    Genre genre;
    int views;
    bool isVIP;
    int ratingSUM;
    int numberOfElector;

    //int* incrementGenre;   //check if we are not puting this in AddMovie


public:

    Movie(int movieID, Genre genre, int views, bool isVIP);
    Movie(const Movie& movie ) = default;
    ~Movie()= default;
    Movie& operator=(const Movie& movie)=default;

    int getId() const;
    int getViews() const;
    void setViews(int viewsToAdd);
    bool getIsVIP()const;
    Genre getGenre() const;
    int getRatingSUM() const;
    void setRatingSUM(int rateToAdd);
    int getNumberOfElector() const;
    void setNumberOfElector(int electorToAdd);
    double getAverageRating()const;

    static int compareMovies(const shared_ptr<Movie> &a, const shared_ptr<Movie> &b);
    static int compareGenre(const shared_ptr<Movie> &a, const shared_ptr<Movie> &b);





};
#endif //STREAMINGDBA1_H_MOVIES_H