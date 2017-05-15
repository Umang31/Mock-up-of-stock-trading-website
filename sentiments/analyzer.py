import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        
        # Store positive words in set
        self.positives_set = set()
        
        # Open positive-words.txt file as read only
        file = open(positives, "r")
        for line in file:
            
            # Check to see if the line starts with comments
            if line.startswith(';') == False:
                
                # Add words in the set while omiting whitespaces
                self.positives_set.add(line.rstrip("\n"))
                
        file.close()
        
        # Store negative words in set    
        self.negatives_set = set()
        
        # Open negative-words.txt file as read only
        file = open(negatives, "r")
        for line in file:
            
            # Check to see if the line starts with comments
            if line.startswith(';') == False:
                
                # Add words in the set while omiting whitespaces
                self.negatives_set.add(line.rstrip("\n"))
                
        file.close()

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        # Instantiate tokenizer
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        
        sum = 0
        
        # Iterate over tokens
        for word in tokens:
            
            # Lowercase the word and check if it is positive or negative
            if word.lower() in self.positives_set:
                sum += 1
                
            elif word.lower() in self.negatives_set:
                sum -= 1
                
            else:
                continue
        
        return sum
