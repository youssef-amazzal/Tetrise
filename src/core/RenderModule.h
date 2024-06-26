#pragma once
#include "../headers/Header.h"
#include "TransformModule.h"
#include "AnimationModule.h"

struct RenderModule {

    explicit RenderModule(flecs::world& world);

    //====================================//
    //              Components            //
    //====================================//

    struct Sprite {
        Texture2D*  texture     = nullptr;
        Rectangle   sourceRect  = {0, 0, 0, 0};
        int originId = 0;

        struct Key {
            UI_ELEMENTS key    = UI_ELEMENTS::UI_INVALID;
        };
    };

    struct Scale {
        float width = 1.0f;
        float height = 1.0f;
    };

    struct Variants {
        std::vector<VARIANTS> values = {};
    };

    struct Repeat {
        enum Type {
            HORIZONTAL,
            VERTICAL,
            BOTH
        } type = BOTH;
    };

    struct Text {
        std::string text;
        float fontSize;
        float spacing;
    };

    struct Shape {
        enum Type {
            RECTANGLE,
            CIRCLE
        } type = RECTANGLE;
    };

    struct Opacity {
        float value = 1.0f;
    };

    struct Expandable {
        int horizontal;
        int vertical;
    };

private:
    //====================================//
    //             Observers              //
    //====================================//

    static void initSprite(flecs::entity entity, Sprite::Key& type);

    //===================================//
    //             Systems               //
    //===================================//


    static void updateScale(flecs::entity entity, Sprite& sprite, Scale& scale, TM::Area& area);

    static void updateSourceRect(
        Sprite::Key& type              , Sprite& sprite,
        Variants& variants      , AM::Frame& animation
    );

    static void render(
        flecs::entity entity            ,
        Sprite::Key& type                      ,Sprite& sprite,
        Scale& scale                    , TM::Area& area,
        const TM::Position& position    , const TM::Depth& depth
    );

    static void renderText(
        flecs::entity entity            , Text& text,
        const TM::Position& position    , const TM::Depth& depth
    );

    //===================================//
    //             Helpers               //
    //===================================//

    static Rectangle buildSourceRect(
        const Sprite::Key& type             , const Sprite& sprite,
        const Variants& variants    , const AM::Frame& animation
    );

    static void renderExpandableTiles(flecs::entity entity, Rectangle destRect);

};

using RM = RenderModule;