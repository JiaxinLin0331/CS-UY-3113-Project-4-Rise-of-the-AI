#ifndef ENTITY_H
#define ENTITY_H

#include "cs3113.h"

enum Direction    { LEFT, UP, RIGHT, DOWN };
enum EntityStatus { ACTIVE, INACTIVE };

enum EntityType {
    PLAYER,
    PATROL,
    HUNTER,
    DRONE,
    PLATFORM,
    JUMP_PAD,
    SPIKES,
    CRATE,
    EXIT,
    SPACESHIP,
    NONE
};

enum AIType {
    NO_AI,
    WANDERER,
    FOLLOWER,
    FLYER
};

class Entity
{
private:
    Vector2 mPosition;
    Vector2 mStartPosition;
    Vector2 mMovement;
    Vector2 mVelocity;
    Vector2 mAcceleration;
    Vector2 mScale;
    Vector2 mColliderDimensions;

    Texture2D mTexture;
    Color mColor;

    EntityType mEntityType;
    EntityStatus mEntityStatus;
    AIType mAIType;
    Direction mDirection;

    int mSpeed;
    int mCurrentFrameIndex;

    float mJumpingPower;
    float mAnimationTime;
    float mAITime;
    float mPatrolDistance;

    bool mIsJumping;
    bool mIsGrounded;
    bool mIsAnimated;

public:
    static constexpr int DEFAULT_SPEED = 250;

    Entity(
        Vector2 position,
        Vector2 scale,
        EntityType entityType,
        Color color = WHITE,
        const char *texturePath = nullptr
    );

    ~Entity();

    void update(float deltaTime, Entity *player);
    void render();

    bool isColliding(Entity *other) const;

    void moveLeft();
    void moveRight();
    void jump();
    void resetMovement();

    void AIActivate(Entity *player);
    void AIWander(float deltaTime);
    void AIFollow(Entity *player);
    void AIFly(float deltaTime);

    Vector2 getPosition() const { return mPosition; }
    Vector2 getVelocity() const { return mVelocity; }
    Vector2 getScale()    const { return mScale; }
    Vector2 getMovement() const { return mMovement; }

    Vector2 getColliderDimensions() const {
        return mColliderDimensions;
    }

    EntityType getEntityType() const { return mEntityType; }
    AIType getAIType() const { return mAIType; }

    bool isActive()   const { return mEntityStatus == ACTIVE; }
    bool isGrounded() const { return mIsGrounded; }

    void setPosition(Vector2 position) { mPosition = position; }
    void setVelocity(Vector2 velocity) { mVelocity = velocity; }
    void setAcceleration(Vector2 acceleration) { mAcceleration = acceleration; }

    void setColliderDimensions(Vector2 dimensions) {
        mColliderDimensions = dimensions;
    }

    void setJumpingPower(float power) { mJumpingPower = power; }
    void setSpeed(int speed) { mSpeed = speed; }
    void setAIType(AIType aiType) { mAIType = aiType; }
    void setGrounded(bool grounded) { mIsGrounded = grounded; }

    void setPatrolDistance(float distance) {
        mPatrolDistance = distance;
    }
};

#endif
