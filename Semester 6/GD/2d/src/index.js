import Phaser from 'phaser';
import leftDudeImg from './assets/leftDude.png'
import rightDudeImg from './assets/rightDude.png'
import platformImg from './assets/platform.png'
import leftBombImg from './assets/leftBomb.png'
import rightBombImg from './assets/rightBomb.png'
import skyImg from './assets/sky.png'
import starImg from './assets/star.png'
import playAgainImg from './assets/playAgain.png'

var initialState = {
    player: null,
    score: 0,
    lives: 3,
    scoreText: null,
    livesText: null,
    orientation: 0,
    bombs: null,
    bombTimeout: 10,
    velocityX: 0
}

var platforms
var leftPlayerState = {...initialState}
var rightPlayerState = {...initialState}
var cursors
var gameOver = false
var bombs = []
var stars
var yPositions = [0, 200, 400]

class MyGame extends Phaser.Scene
{

    constructor() {
        super('playing');
    }

    preload ()
    {
        this.load.image('sky', skyImg)
        this.load.image('star', starImg)
        this.load.image('leftBomb', leftBombImg)
        this.load.image('rightBomb', rightBombImg)
        this.load.image('platform', platformImg)
        this.load.spritesheet('leftDude', leftDudeImg, { frameWidth: 32, frameHeight: 48 })
        this.load.spritesheet('rightDude', rightDudeImg, { frameWidth: 32, frameHeight: 48 })
    }

    create ()
    {
        console.log("Playing")
        this.add.image(400, 400, 'sky')

        platforms = this.physics.add.staticGroup()

        platforms.create(200, 700, 'platform')
            .setScale(0.7, 1)
            .refreshBody()

        platforms.create(600, 700, 'platform')
            .setScale(0.7, 1)
            .refreshBody()

        platforms.create(400, 500, 'platform')

        platforms.create(200, 300, 'platform')
            .setScale(0.7, 1)
            .refreshBody()

        platforms.create(600, 300, 'platform')
            .setScale(0.7, 1)
            .refreshBody()

        platforms.create(400, 100, 'platform')

        leftPlayerState.player = this.physics.add.sprite(250, 600, 'leftDude')
        rightPlayerState.player = this.physics.add.sprite(550, 600, 'rightDude')

        leftPlayerState.player.setBounce(0.4)
        rightPlayerState.player.setBounce(0.4)

        leftPlayerState.scoreText = this.add.text(16, 16, `score: ${leftPlayerState.score}`, { fontSize: '24px', fill: '#0000ff' });
        leftPlayerState.livesText = this.add.text(16, 48, `lives: ${leftPlayerState.lives}`, { fontSize: '24px', fill: '#0000ff' });

        rightPlayerState.scoreText = this.add.text(800-150, 16, `score: ${rightPlayerState.score}`, { fontSize: '24px', fill: '#ff0000' });
        rightPlayerState.livesText = this.add.text(800-150, 48, `lives: ${rightPlayerState.lives}`, { fontSize: '24px', fill: '#ff0000' });

        this.physics.add.collider(leftPlayerState.player, platforms)
        this.physics.add.collider(rightPlayerState.player, platforms)

        this.setupPlayerAnim('leftDude')
        this.setupPlayerAnim('rightDude')

        leftPlayerState.bombs = this.physics.add.group()
        rightPlayerState.bombs = this.physics.add.group()

        this.physics.add.overlap(platforms, leftPlayerState.bombs, this.bombHitsPlatform, null, this)
        this.physics.add.overlap(platforms, rightPlayerState.bombs, this.bombHitsPlatform, null, this)

        this.physics.add.overlap(
            leftPlayerState.player,
            rightPlayerState.bombs,
            (_, bomb)=>
                this.bombHitsPlayer(leftPlayerState, bomb),
            null,
            this
        )

        this.physics.add.overlap(
            rightPlayerState.player,
            leftPlayerState.bombs,
            (_, bomb)=>
                this.bombHitsPlayer(rightPlayerState, bomb),
            null,
            this
        )

        cursors = this.input.keyboard.addKeys(
            {
                w:Phaser.Input.Keyboard.KeyCodes.W,
                s:Phaser.Input.Keyboard.KeyCodes.S,
                a:Phaser.Input.Keyboard.KeyCodes.A,
                d:Phaser.Input.Keyboard.KeyCodes.D,
                up:Phaser.Input.Keyboard.KeyCodes.UP,
                down:Phaser.Input.Keyboard.KeyCodes.DOWN,
                left:Phaser.Input.Keyboard.KeyCodes.LEFT,
                right:Phaser.Input.Keyboard.KeyCodes.RIGHT,
                leftShoot: Phaser.Input.Keyboard.KeyCodes.SPACE,
                rightShoot: Phaser.Input.Keyboard.KeyCodes.ENTER
            })

        stars = this.physics.add.group({
            key: 'star',
            repeat: 4,
            setXY: { x: 120, y: yPositions[Math.floor(Math.random() * yPositions.length)], stepX: 136 }
        });

        stars.children.iterate(function (child) {
             child.setBounceY(Phaser.Math.FloatBetween(0.4, 0.8));
        })

        this.physics.add.collider(stars, platforms)
        this.physics.add.overlap(leftPlayerState.player, stars,
            (_, star) => this.collectStar(leftPlayerState, star),
            null, this)
        this.physics.add.overlap(rightPlayerState.player, stars,
            (_, star) => this.collectStar(rightPlayerState, star),
            null, this)
    }

    collectStar(state, star){
        star.disableBody(true, true)
        state.score += 10
        state.scoreText.setText(`score: ${state.score}`)
        if (stars.countActive(true) === 0) {
            stars.children.iterate(function (child) {

                child.enableBody(true, child.x,  yPositions[Math.floor(Math.random() * yPositions.length)], true, true);

            });
        }
    }

    bombHitsPlayer(state, bomb){
        state.velocityX = bomb.orientation * 800
        this.destroyBomb(bomb)
    }

    bombHitsPlatform(platform, bomb){
       this.destroyBomb(bomb)
    }

    destroyBomb(bomb){
        bomb.disableBody(true, true)
        bombs = bombs.filter(b=>b!==bomb)
    }

    update()
    {
        if(gameOver){
            leftPlayerState.score += leftPlayerState.lives * 10
            rightPlayerState.score += rightPlayerState.lives * 10

            this.scene.start("gameOver");
            return
        }
        this.setupKeys()
        this.isDead(leftPlayerState)
        this.isDead(rightPlayerState)

        var bombsToBeDeleted = []
        bombs.forEach(b=>{
            if(b.x > 800 || b.y > 800 || b.x < 0 || b.y < 0){
                b.disableBody(true, true)
                bombsToBeDeleted.push(b)
            }
        })
        bombs = bombs.filter(b=>!bombsToBeDeleted.includes(b))
    }

    isDead(state){
        if(state.player.y > 800){
            state.player.y = 300
            state.player.x = 400
            state.lives -= 1
            state.livesText.text = `lives: ${state.lives}`
            gameOver = state.lives === 0
        }
    }

    setupKeys(){
        //RIGHT PLAYER
        if (cursors.left.isDown)
        {
            //rightPlayerState.player.setVelocityX(-160);
            this.adjustVelocity(rightPlayerState, -160)


            rightPlayerState.player.anims.play('rightDudeLeft', true);
            rightPlayerState.orientation = -1
        }
        else if (cursors.right.isDown)
        {
            //rightPlayerState.player.setVelocityX(160);
            this.adjustVelocity(rightPlayerState, 160)

            rightPlayerState.player.anims.play('rightDudeRight', true);
            rightPlayerState.orientation = 1
        }
        else
        {
            this.adjustVelocity(rightPlayerState, 0)

            rightPlayerState.player.anims.play('rightDudeTurn');
            rightPlayerState.orientation = 0
        }

        if (cursors.up.isDown && rightPlayerState.player.body.touching.down)
        {
            rightPlayerState.player.setVelocityY(-330);
        }

        // LEFT PLAYER
        if (cursors.a.isDown)
        {
            this.adjustVelocity(leftPlayerState, -160)

            leftPlayerState.player.anims.play('leftDudeLeft', true);
            leftPlayerState.orientation = -1
        }
        else if (cursors.d.isDown)
        {
            this.adjustVelocity(leftPlayerState, 160)

            leftPlayerState.player.anims.play('leftDudeRight', true);
            leftPlayerState.orientation = 1
        }
        else
        {
           this.adjustVelocity(leftPlayerState, 0)

            leftPlayerState.player.anims.play('leftDudeTurn');
            leftPlayerState.orientation = 0
        }

        if (cursors.w.isDown && leftPlayerState.player.body.touching.down)
        {
            leftPlayerState.player.setVelocityY(-330);
        }

        if(cursors.leftShoot.isDown && leftPlayerState.orientation !== 0){
            this.createBomb('leftBomb', leftPlayerState)
        }

        if(cursors.rightShoot.isDown && rightPlayerState.orientation !== 0){
            this.createBomb('rightBomb', rightPlayerState)
        }
        leftPlayerState.bombTimeout -= 1
        rightPlayerState.bombTimeout -= 1
    }

    adjustVelocity(state, value){
        state.player.setVelocityX(state.velocityX + value);
        if(state.velocityX > 0)
            state.velocityX -= 50
        if(state.velocityX < 0)
            state.velocityX += 50
    }

    createBomb(name, state){
        if(state.bombTimeout > 0){
            return
        }
        state.bombTimeout = 10
        var bomb = state.bombs.create(
            state.player.x,
            state.player.y,
            name
        );
        bomb.orientation = state.orientation
        bomb.setBounce(1)
        bomb.setVelocity(800*state.orientation, 0)
        bomb.allowGravity = false
        bombs.push(bomb)
    }

    setupPlayerAnim(player){
        this.anims.create({
            key: `${player}Left`,
            frames: this.anims.generateFrameNumbers(player, { start: 0, end: 3 }),
            frameRate: 10,
            repeat: -1
        });

        this.anims.create({
            key: `${player}Turn`,
            frames: [ { key: player, frame: 4 } ],
            frameRate: 20
        });

        this.anims.create({
            key: `${player}Right`,
            frames: this.anims.generateFrameNumbers(player, { start: 5, end: 8 }),
            frameRate: 10,
            repeat: -1
        });
    }
}

class GameOver extends Phaser.Scene{
    constructor() {
        super('gameOver');
    }

    preload(){
        this.load.image('sky', skyImg)
        this.load.image('playAgain', playAgainImg)

    }

    create() {
        console.log("Game over")
        this.add.image(400, 400, 'sky')

        leftPlayerState.scoreText = this.add.text(16, 16, `score: ${leftPlayerState.score}`, { fontSize: '24px', fill: '#0000ff' });
        leftPlayerState.livesText = this.add.text(16, 48, `lives: ${leftPlayerState.lives}`, { fontSize: '24px', fill: '#0000ff' });

        rightPlayerState.scoreText = this.add.text(800-150, 16, `score: ${rightPlayerState.score}`, { fontSize: '24px', fill: '#ff0000' });
        rightPlayerState.livesText = this.add.text(800-150, 48, `lives: ${rightPlayerState.lives}`, { fontSize: '24px', fill: '#ff0000' });


        status = ''
        if(leftPlayerState.score === rightPlayerState.score)
            status = 'IT IS A TIE!'
        else if(leftPlayerState.score > rightPlayerState.score)
            status = 'BLUE PLAYER WON'
        else
            status = 'RED PLAYER WON'

        this.add.text(170, 200, status, { fontSize: '64px', fill: '#00ff00' })

        this.add.text(250, 300, 'GAME OVER', { fontSize: '64px', fill: '#00ff00' })

        this.add.text(230, 400, 'PLAY AGAIN', { fontSize: "64px", fill: '#00ff00' })
            .setInteractive()
            .on('pointerdown', () => this.playTheGame());

    }

    playTheGame() {
        gameOver = false
        leftPlayerState = {...initialState}
        rightPlayerState = {...initialState}
        this.scene.start("playing");
    }

}

const config = {
    type: Phaser.AUTO,
    parent: 'phaser-example',
    width: 800,
    height: 800,
    physics: {
        default: 'arcade',
        arcade: {
            gravity: { y: 250 },
            debug: false
        }
    },
    scene: [MyGame, GameOver]
};

const game = new Phaser.Game(config);
