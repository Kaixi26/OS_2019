#!/usr/bin/env stack
-- stack --resolver lts-13.7 script 

import System.IO
import System.Random
import Control.Monad
import qualified Data.Vector as V
import qualified Turtle as T
import qualified Data.Text as Text

fstNameFile = "./data/first-names.txt"
sndNameFile = "./data/middle-names.txt"


distribute :: Int -> [a] -> [[a]]
distribute _ [] = []
distribute n s = let (l,r) = splitAt n s in
    l : (distribute n r)

randPerson :: V.Vector String -> V.Vector String -> IO String
randPerson v1 v2 = do
    v1_i <- randomRIO (0, length v1 - 1)
    v2_i <- randomRIO (0, length v2 - 1)
    age  <- randomRIO (0, 100::Int)
    return $ concat
        [ "\""
        , v1 V.! v1_i
        , " "
        , v2 V.! v2_i
        , "\" "
        , show age
        ]

main = do
    fsth <- openFile fstNameFile ReadMode
    sndh <- openFile sndNameFile ReadMode
    fstNames <- liftM (map init . lines) (hGetContents fsth)
    sndNames <- liftM (map init . lines) (hGetContents sndh)
    let fstNamesVec = V.fromList fstNames
        sndNamesVec = V.fromList sndNames
    let total = 1000000
        batch = 1000
    commands <- liftM (map (((++) "./persondb -m ") . unwords) . distribute batch) (replicateM total (randPerson fstNamesVec sndNamesVec))
    mapM_ (\cmd -> T.stdout $ T.inshell (Text.pack$ cmd++" ") T.stdin) commands
    hClose fsth
    hClose sndh
    return ()
