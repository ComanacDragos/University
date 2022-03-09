import Phaser from 'phaser';
import leftDudeImg from './assets/leftDude.png'
import rightDudeImg from './assets/rightDude.png'
import platformImg from './assets/platform.png'
import leftProjectileImg from './assets/leftProjectile.png'
import rightProjectileImg from './assets/rightProjectile.png'
import skyImg from './assets/sky.png'
import starImg from './assets/star.png'


var platforms
var leftPlayer
var rightPlayer

class MyGame extends Phaser.Scene
{

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


    }

    update()
    {
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
            gravity: { y: 300 },
            debug: false
        }
    },
    scene: MyGame
};

const game = new Phaser.Game(config);
