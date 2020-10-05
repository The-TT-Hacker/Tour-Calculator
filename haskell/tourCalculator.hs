import Data.Dates

-- type Tour = [Tour] maybe not needed anymore?
type Lat = Float
type Lon = Float


data Tour = Tournament { name     :: String
                       , location :: (Lat, Lon)
                       , start    :: DateTime
                       , end      :: DateTime
                       , next     :: Tour
                       }
          | Home { next :: Tour }
          | End


data Weights = Weights { travelDistance :: Float
                       , prizeMoney     :: Float
                       , numTournaments :: Float
                       }





allTours :: [Tour]
allTours = [] -- TODO: add tours


bestTour :: [Tour] -> Tour
bestTour ts = undefined


cost :: Tour -> Weights -> Float
cost t w = undefined



