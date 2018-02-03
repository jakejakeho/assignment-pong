//
// Created by Daniel on 24/12/2017.
//

#ifndef INC_SCORE_H
#define INC_SCORE_H


#include "sprite.h"
#include "config.h"

/**
 * Platform Sprite for the Pong game.
 */
class Score: public Sprite {
public:
    explicit Score(libsc::Lcd* pLcd, bool);

    /**
     * Moves the platform one step to the left.
     */
    void render() override;
    void addScore();
    int score = 0;
};


#endif //INC_PLATFORM_H
