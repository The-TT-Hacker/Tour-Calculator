#!/usr/bin/env python

import sys
import argparse
import csv
import datetime


def unix_time( datestring ):
    day   = int( datestring[0:2] )
    month = int( datestring[3:5] )
    year  = int( datestring[6:10] )
    dt = datetime.datetime( year, month, day )
    return int( dt.replace(tzinfo=datetime.timezone.utc).timestamp() )
    
def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument( '--input-file', type=str, help='file to read' )
    return parser.parse_args()

def main( args ):
    with open( args.input_file, "r" ) as infile:
        reader = csv.reader( infile )
        for row in reader:
            startdate = unix_time( row[1] )
            enddate   = unix_time( row[2] )
            duration = enddate - startdate
            print( ",".join( (row[0], str(startdate), str(duration)) ) )
    
if __name__ == '__main__':
    sys.exit( main(get_args()) )
