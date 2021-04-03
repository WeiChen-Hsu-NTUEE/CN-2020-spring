#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <ctime>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int score = 0;
time_t time_ = time(0);
//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};
class wall
{
    public:
        SDL_Rect wall_1;
        SDL_Rect wall_2;
        SDL_Rect wall_3;
        SDL_Rect wall_4;
        SDL_Rect wall_5;
        void setstage();
};
void wall::setstage()
{
    srand(time(0));
    switch(rand()%3){
        case 0:
            wall_1.x = 300;wall_1.y = 40;wall_1.w = 40;wall_1.h = 400;
            wall_2.x = 420;wall_2.y = 250;wall_2.w = 40;wall_2.h = 130;
            wall_3.x = 500;wall_3.y = 100;wall_3.w = 140;wall_3.h = 80;
            wall_4.x = 50;wall_4.y = 50;wall_4.w = 150;wall_4.h = 80;
            wall_5.x = 100;wall_5.y = 200;wall_5.w = 50;wall_5.h = 200;
            break;
        case 1:
            wall_1.x = 260;wall_1.y = 170;wall_1.w = 180;wall_1.h = 100;
            wall_2.x = 550;wall_2.y = 0;wall_2.w = 40;wall_2.h = 200;
            wall_3.x = 480;wall_3.y = 320;wall_3.w = 40;wall_3.h = 160;
            wall_4.x = 150;wall_4.y = 320;wall_4.w = 40;wall_4.h = 160;
            wall_5.x = 80;wall_5.y = 0;wall_5.w = 40;wall_5.h = 220;
            break;
        case 2:
            wall_1.x = 500;wall_1.y = 0;wall_1.w = 40;wall_1.h = 100;
            wall_2.x = 0;wall_2.y = 140;wall_2.w = 300;wall_2.h = 120;
            wall_3.x = 360;wall_3.y = 140;wall_3.w = 280;wall_3.h = 120;
            wall_4.x = 130;wall_4.y = 380;wall_4.w = 80;wall_4.h = 60;
            wall_5.x = 480;wall_5.y = 340;wall_5.w = 80;wall_5.h = 140;
            break;
    }
}
//The dot that will move around on the screen
class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 25;
		static const int DOT_HEIGHT = 25;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 1;

		//Initializes the variables
		Dot();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot and checks collision
		void move(wall& stage);

		//Shows the dot on the screen
		void render();
        int getmPosX();
        int getmPosY();
        SDL_Rect mCollider;
    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

		//Dot's collision box

};

class Food
{
public:

    int posX, posY;
    static const int FOOD_WIDTH = 20;
    static const int FOOD_HEIGHT = 20;
    SDL_Rect c;

    void setfood(Dot& dot, wall& wall);
    int get_food_posX();
    int get_food_posY();
    bool checkCollision(SDL_Rect&);
};

void Food::setfood(Dot& dot, wall& wall)
{
    bool valid = false;
    while (!valid){
        posX = get_food_posX();
        posY = get_food_posY();
        valid = true;
        if (posX-dot.getmPosX()<=FOOD_WIDTH && posX-dot.getmPosX()>=-FOOD_WIDTH && posY-dot.getmPosY()<=FOOD_HEIGHT && posY-dot.getmPosY()>=-FOOD_HEIGHT){
            valid = false;
        }
        if (checkCollision(wall.wall_1)){
            valid = false;
        }
        if (checkCollision(wall.wall_2)){
            valid = false;
        }
        if (checkCollision(wall.wall_3)){
            valid = false;
        }
        if (checkCollision(wall.wall_4)){
            valid = false;
        }
        if (checkCollision(wall.wall_5)){
            valid = false;
        }
    }
    c.h = FOOD_HEIGHT;
    c.w = FOOD_WIDTH;
    c.x = posX;
    c.y = posY;
}

int Food::get_food_posX()
{
    double x;
    srand(rand());
    x = rand()% (SCREEN_WIDTH-FOOD_WIDTH);
    return x;
}

int Food::get_food_posY()
{
    double y;
    srand(rand());
    y = rand()% (SCREEN_HEIGHT-FOOD_HEIGHT);
    return y;
}

bool Food::checkCollision(SDL_Rect& wall)
{
    bool valid = false;
    if (posX-wall.x<=wall.w+FOOD_WIDTH && posX-wall.x>=-FOOD_WIDTH && posY-wall.y<=wall.h+FOOD_HEIGHT && posY-wall.y>=-FOOD_HEIGHT){
        valid = true;
    }
    return valid;
}

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia(int);

//Frees media and shuts down SDL
void close();

//Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gDotTexture;
LTexture gTextTexture;
LTexture gTimeTexture;
LTexture gGameOverTexture;
TTF_Font *gFont = NULL;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

Dot::Dot()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

	//Set collision box dimension
	mCollider.w = DOT_WIDTH;
	mCollider.h = DOT_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Dot::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN&& e.key.repeat == 0)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL;
                if(loadMedia(2)){
                mVelX = 0;
                //if(mVelY<-DOT_VEL) mVelY = -DOT_VEL;
                break;
                }
            case SDLK_DOWN: mVelY += DOT_VEL;
                loadMedia(3);
                mVelX = 0;
                //if(mVelY>DOT_VEL) mVelY = DOT_VEL;
                break;
            case SDLK_LEFT: mVelX -= DOT_VEL;
                loadMedia(4);
                mVelY = 0;
                //if(mVelX<-DOT_VEL) mVelX = -DOT_VEL;
                break;
            case SDLK_RIGHT: mVelX += DOT_VEL;
                loadMedia(1);
                mVelY = 0;
                //if(mVelX>DOT_VEL) mVelX = DOT_VEL;
                break;
        }
    }
}

void Dot::move( wall& stage )
{
    //Move the dot left or right
    mPosX += mVelX;
	mCollider.x = mPosX;
    //If the dot collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) || checkCollision( mCollider, stage.wall_1 ) || checkCollision( mCollider, stage.wall_2 )
       || checkCollision( mCollider, stage.wall_3 ) || checkCollision( mCollider, stage.wall_4 ) || checkCollision( mCollider, stage.wall_5 ))
    {
        //Move back
        mPosX -= mVelX;
		mCollider.x = mPosX;
    }
    //Move the dot up or down
    mPosY += mVelY;
	mCollider.y = mPosY;
    //If the dot collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) || checkCollision( mCollider, stage.wall_1 ) || checkCollision( mCollider, stage.wall_2 )
       || checkCollision( mCollider, stage.wall_3 ) || checkCollision( mCollider, stage.wall_4 ) || checkCollision( mCollider, stage.wall_5 ))
    {
        //Move back
        mPosY -= mVelY;
		mCollider.y = mPosY;
    }
}

void Dot::render()
{
    //Show the dot
	gDotTexture.render( mPosX, mPosY );
}

int Dot::getmPosX()
{
    return mPosX;
}

int Dot::getmPosY()
{
    return mPosY;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
	return success;
}

bool loadMedia(int a)
{
	//Loading success flag
	bool success = true;
	//Load press texture
	switch (a){
	    case 0:break;
    case 1:
        if( !gDotTexture.loadFromFile( "eat_man/eat_man_right.png" ) )
        {
            printf( "Failed to load dot texture!\n" );
            success = false;
        }
        break;
    case 2:
        if( !gDotTexture.loadFromFile( "eat_man/eat_man_up.png" ) )
            {
            printf( "Failed to load dot texture!\n" );
            success = false;
        }
        break;
    case 3:
        if( !gDotTexture.loadFromFile( "eat_man/eat_man_down.png" ) )
            {
            printf( "Failed to load dot texture!\n" );
            success = false;
        }
        break;
    case 4:
        if( !gDotTexture.loadFromFile( "eat_man/eat_man_left.png" ) )
            {
            printf( "Failed to load dot texture!\n" );
            success = false;
        }
        break;
    case 5:
        if( !gGameOverTexture.loadFromFile("gameover.jpg"))
        {
            printf( "Failed to load dot texture!\n");
            success = false;
        }
        return false;
	}
	gFont = TTF_OpenFont( "arial.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 255, 255, 255 };
        if( !gTextTexture.loadFromRenderedText( (std::string("Score: ") + std::to_string(score) ).c_str(), textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }

        if(!gTimeTexture.loadFromRenderedText( (std::string("time: ") + std::to_string(60-(int)time(0)+time_) ).c_str(), textColor ) )
        {
            success = false;
        }
    }
    return success;
}

void close()
{
	//Free loaded images
	gDotTexture.free();
    gTextTexture.free();
    gTimeTexture.free();
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia(1) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			//The dot that will be moving around on the screen
			Dot dot;


			//Set the wall
            wall stage;
            stage.setstage();

            //set the food
            Food food;
            food.setfood(dot, stage);


			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the dot
					dot.handleEvent( e );
				}
                if (checkCollision(dot.mCollider, food.c)){
                    food.setfood(dot, stage);
                    score++;
                    loadMedia(0);
				}
				//Move the dot and check collision
				dot.move( stage );
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
				SDL_RenderClear( gRenderer );

				//Render wall
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderDrawRect( gRenderer, &stage.wall_1 );
				SDL_RenderDrawRect( gRenderer, &stage.wall_2 );
				SDL_RenderDrawRect( gRenderer, &stage.wall_3 );
				SDL_RenderDrawRect( gRenderer, &stage.wall_4 );
				SDL_RenderDrawRect( gRenderer, &stage.wall_5 );
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
				SDL_RenderFillRect( gRenderer, &food.c );
				//Render dot
				dot.render();

				gTextTexture.render(520, 0);
                gTimeTexture.render(520, 40);
                loadMedia(0);
                if ((int)time(0)-time_ == 60){
                    while(1){
                        loadMedia(5);
                        gGameOverTexture.render(80, 50);
                        SDL_RenderPresent( gRenderer );
                        if((int)time(0)-time_ == 65){
                            return 0;
                        }
                    }
                }

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
