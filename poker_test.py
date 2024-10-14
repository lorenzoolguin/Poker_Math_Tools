import math
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import random
import time


class Card:
    def __init__(self, rank, suit):
        self.rank = rank
        self.suit = suit

    def __str__(self):
        return f"{self.rank}{self.suit}"


class Player:
    def __init__(self, name, chips=1000):
        self.name = name
        self.chips = chips
        self.hand = []

    def __str__(self):
        return self.name

    def bet(self, amount):
        if amount > self.chips:
            raise ValueError("Not enough chips to bet this amount.")
        self.chips -= amount
        return amount

    def win(self, amount):
        self.chips += amount

    def reset(self):
        self.hand = []

    def __hash__(self):
        return hash(self.name)

    def __eq__(self, other):
        if isinstance(other, Player):
            return self.name == other.name
        return False


class Deck:
    ranks = ["2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"]
    suits = ["h", "d", "c", "s"]

    def __init__(self):
        self.cards = [Card(rank, suit) for suit in self.suits for rank in self.ranks]
        self.burn_pile = []
        self.shuffle()

    def shuffle(self):
        random.shuffle(self.cards)

    def deal(self, num_cards=1):
        burn_card = self.cards.pop()
        self.burn_pile.append(burn_card)
        return [self.cards.pop() for _ in range(num_cards)]

    def get_burned_cards(self):
        return self.burn_pile

    def reset(self):
        self.__init__()

    def __len__(self):
        return len(self.cards)


class Poker_Game:
    def __init__(self, num_players, small_blind=10, big_blind=20):
        self.deck = Deck()
        self.players = [Player(f"Player {i+1}") for i in range(num_players)]
        self.community_cards = []
        self.pot = 0
        self.current_bet = 0
        self.round = 0
        self.button_index = 0
        self.small_blind = small_blind
        self.big_blind = big_blind
        self.player_contributions = {player: 0 for player in self.players}
        # self.player_betting_round_contribution = {player: 0 for player in self.players}

    def deal_hole_cards(self):
        for player in self.players:
            player.hand = self.deck.deal(2)

    def display_player_hands(self):
        for player in self.players:
            print(f"{player}: {player.hand[0]}, {player.hand[1]}")

    def start_game(self):
        print("Starting a new poker hand!")
        self.post_blinds()  # Post blinds at the beginning of the hand
        self.deal_hole_cards()
        self.display_player_hands()

    def next_round(self):
        if self.round == 1:
            print("Dealing the Flop")
            self.community_cards += self.deck.deal(3)
        elif self.round in [2, 3]:
            print("Dealing the Turn" if self.round == 2 else "Dealing the River")
            self.community_cards += self.deck.deal(1)
        # self.round += 1
        self.display_community_cards()

    def display_community_cards(self):
        print(
            f'Community Cards: {", ".join(str(card) for card in self.community_cards)}'
        )

    def post_blinds(self):
        # Posting small blind
        small_blind_index = (self.button_index + 1) % len(self.players)
        small_blind_player = self.players[small_blind_index]
        small_blind_player.bet(self.small_blind)
        self.pot += self.small_blind
        self.player_contributions[small_blind_player] += self.small_blind
        print(f"{small_blind_player} posts small blind: {self.small_blind}")

        # Posting big blind
        big_blind_index = (self.button_index + 2) % len(self.players)
        big_blind_player = self.players[big_blind_index]
        big_blind_player.bet(self.big_blind)
        self.pot += self.big_blind
        self.player_contributions[big_blind_player] += self.big_blind
        self.current_bet = self.big_blind
        print(f"{big_blind_player} posts big blind: {self.big_blind}")

        # Print current pot size and player contributions after blinds
        print(f"Current pot size: {self.pot}")
        print("Player contributions:")
        for player in self.players:
            print(f"  {player}: {self.player_contributions[player]}")

    def betting_round(self):
        print(f"\nStarting betting round {self.round}")
        starting_index = (
            (self.button_index + 3) % len(self.players)
            if self.round == 0
            else self.button_index
        )
        new_raise = 0
        for i in range(len(self.players)):
            player_index = (starting_index + i) % len(self.players)
            player = self.players[player_index]
            max_contribution = 0
            # print(self.players)
            for i in range(len(self.players)):
                player_index_x = (starting_index + i) % len(self.players)
                player_x = self.players[player_index_x]
                if self.player_contributions[player_x] > max_contribution:
                    max_contribution = self.player_contributions[player_x]
            print(f"Max Contribution: {max_contribution}")
            # need to a add a current round contribution value. not sure exactly how yet.
            if player.chips <= 0:
                print(f"{player} is all-in. No further betting.")
                continue

            # to_call = self.current_bet - self.player_contributions[player]
            to_call = max_contribution - self.player_contributions[player]

            action = input(
                f"{player}, your action (call {to_call}/fold/raise/check): "
            ).lower()

            if action == "fold":
                self.players.remove(player)
                print(f"{player} folds")
            elif action == "raise":
                while True:
                    try:
                        raise_amount = int(input("Enter total bet amount: "))
                        if raise_amount <= self.current_bet:
                            print(
                                f"Raise amount must be greater than the current bet of {self.current_bet}."
                            )
                            continue
                        additional_bet = (
                            raise_amount - self.player_contributions[player]
                        )
                        if additional_bet > player.chips:
                            print(
                                f"Not enough chips. You only have {player.chips} chips."
                            )
                            continue
                        # self.pot += player.bet(additional_bet)
                        self.pot += player.bet(raise_amount)
                        # self.player_contributions[player] += additional_bet
                        self.player_contributions[player] += raise_amount
                        self.current_bet = raise_amount
                        print(f"{player} raises to {raise_amount}")
                        break
                    except ValueError:
                        print("Please enter a valid number.")
            elif action == "check":
                if to_call == 0:
                    print(f"{player} checks")
                else:
                    print(f"{player} cannot check. Must call {to_call} or fold.")
                    while True:
                        action = input(
                            f"{player}, your action (call {to_call}/fold): "
                        ).lower()
                        if action == "fold":
                            self.players.remove(player)
                            print(f"{player} folds")
                            break
                        elif action == "call":
                            if player.chips < to_call:
                                print(
                                    f"{player} does not have enough chips to call. All-in!"
                                )
                                all_in_amount = player.chips
                                self.pot += player.bet(all_in_amount)
                                self.player_contributions[player] += all_in_amount
                            else:
                                self.pot += player.bet(to_call)
                                self.player_contributions[player] += to_call
                            print(f"{player} calls {to_call}")
                            break
                        else:
                            print("Invalid action. Please choose 'call' or 'fold'.")
            else:  # call
                if player.chips < to_call:
                    print(f"{player} does not have enough chips to call. All-in!")
                    all_in_amount = player.chips
                    self.pot += player.bet(all_in_amount)
                    self.player_contributions[player] += all_in_amount
                else:
                    self.pot += player.bet(to_call)
                    self.player_contributions[player] += to_call
                print(f"{player} calls {to_call}")

            # Print current pot size and player contributions after each action
            print(f"Current pot size: {self.pot}")
            print("Player contributions:")
            for p in self.players:
                print(f"  {p}: {self.player_contributions[p]}")

        self.round += 1

    def play_hand(self):
        self.start_game()
        for _ in range(4):  # Pre-flop, Flop, Turn, River
            self.betting_round()
            if len(self.players) == 1:
                print(f"{self.players[0]} wins {self.pot} chips!")
                return
            if self.round <= 3:
                self.next_round()

        # Showdown
        print("\nShowdown!")
        self.display_community_cards()
        self.display_player_hands()
        winner = random.choice(self.players)  # Simplified winner selection
        print(f"{winner} wins {self.pot} chips!")


def reset_hand(self):
    self.deck.reset()
    self.community_cards = []
    self.pot = 0
    self.current_bet = 0
    self.round = 0
    self.button_index = (self.button_index + 1) % len(self.players)
    self.player_contributions = {
        player: 0 for player in self.players
    }  # Reset contributions
    for player in self.players:
        player.hand = []


def main():
    num_players = int(input("Enter the number of players: "))
    game = Poker_Game(num_players)

    while True:
        game.play_hand()
        play_again = input("Press Enter to play another hand or 'q' to quit: ")
        if play_again.lower() == "q":
            break
        game.reset_hand()


if __name__ == "__main__":
    main()

# TODO: implement poker hand winner logic instead of random selection
# TODO: set up data collection for simulation running
# TODO: set up simple UI for ease of use
# TODO: test/debug w/ greater than 2 players
