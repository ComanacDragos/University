import Phaser from 'phaser';
import leftDudeImg from './assets/leftDude.png'
import rightDudeImg from './assets/rightDude.png'
import platformImg from './assets/platform.png'
import leftProjectileImg from './assets/leftProjectile.png'
import rightProjectileImg from './assets/rightProjectile.png'
import skyImg from './assets/sky.png'
import starImg from './assets/star.png'
import playAgainImg from './assets/playAgain.png'

var initialState = {
    player: null,
    score: 0,
    lives: 1,
    scoreText: null,
    livesText: null,
}

var platforms
var leftPlayerState = {...initialState}
var rightPlayerState = {...initialState}
var cursors
var gameOver = false

class MyGame extends Phaser.Scene
{

    constructor() {
        super('playing');
    }

    preload ()
    {
        this.load.image('sky', skyImg)
        this.load.image('star', starImg)
        this.load.image('leftProjectile', leftProjectileImg)
        this.load.image('rightProjectile', rightProjectileImg)
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

        leftPlayerState.scoreText = this.add.text(16, 16, 'score: 0', { fontSize: '24px', fill: '#0000ff' });
        leftPlayerState.livesText = this.add.text(16, 48, `lives: ${leftPlayerState.lives}`, { fontSize: '24px', fill: '#0000ff' });

        rightPlayerState.scoreText = this.add.text(800-128, 16, 'score: 0', { fontSize: '24px', fill: '#ff0000' });
        rightPlayerState.livesText = this.add.text(800-128, 48, `lives: ${rightPlayerState.lives}`, { fontSize: '24px', fill: '#ff0000' });

        this.physics.add.collider(leftPlayerState.player, platforms)
        this.physics.add.collider(rightPlayerState.player, platforms)

        this.setupPlayerAnim('leftDude')
        this.setupPlayerAnim('rightDude')

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
            });
    }

    update()
    {
        if(gameOver){
            this.scene.start("gameOver");
            return
        }
        this.setupKeys()
        this.isDead(leftPlayerState)
        this.isDead(rightPlayerState)
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
        if (cursors.left.isDown)
        {
            rightPlayerState.player.setVelocityX(-160);

            rightPlayerState.player.anims.play('rightDudeLeft', true);
        }
        else if (cursors.right.isDown)
        {
            rightPlayerState.player.setVelocityX(160);

            rightPlayerState.player.anims.play('rightDudeRight', true);
        }
        else
        {
            rightPlayerState.player.setVelocityX(0);

            rightPlayerState.player.anims.play('rightDudeTurn');
        }

        if (cursors.up.isDown && rightPlayerState.player.body.touching.down)
        {
            rightPlayerState.player.setVelocityY(-330);
        }

        if (cursors.a.isDown)
        {
            leftPlayerState.player.setVelocityX(-160);

            leftPlayerState.player.anims.play('leftDudeLeft', true);
        }
        else if (cursors.d.isDown)
        {
            leftPlayerState.player.setVelocityX(160);

            leftPlayerState.player.anims.play('leftDudeRight', true);
        }
        else
        {
            leftPlayerState.player.setVelocityX(0);

            leftPlayerState.player.anims.play('leftDudeTurn');
        }

        if (cursors.w.isDown && leftPlayerState.player.body.touching.down)
        {
            leftPlayerState.player.setVelocityY(-330);
        }
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

        leftPlayerState.scoreText = this.add.text(16, 16, 'score: 0', { fontSize: '24px', fill: '#0000ff' });
        leftPlayerState.livesText = this.add.text(16, 48, `lives: ${leftPlayerState.lives}`, { fontSize: '24px', fill: '#0000ff' });

        rightPlayerState.scoreText = this.add.text(800-128, 16, 'score: 0', { fontSize: '24px', fill: '#ff0000' });
        rightPlayerState.livesText = this.add.text(800-128, 48, `lives: ${rightPlayerState.lives}`, { fontSize: '24px', fill: '#ff0000' });


        status = ''
        if(leftPlayerState.score === rightPlayerState.score)
            status = 'IT IS A TIE!'
        else if(leftPlayerState.score > rightPlayerState.score)
            status = 'LEFT PLAYER WON'
        else
            status = 'RIGHT PLAYER WON'

        this.add.text(200, 200, status, { fontSize: '64px', fill: '#00ff00' })

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
